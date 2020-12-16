////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"

#include <QDebug>
#include <QNetworkDatagram>

#include <osc++.hpp>

#include <regex>
#include <stdexcept>
#include <string> // std::stoi

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
namespace
{

auto to_name(const value& v)
{
    QString name(v.to_string().data());

    auto p = name.lastIndexOf('/');
    if(p >= 0) name.remove(0, p + 1);

    p = name.lastIndexOf('.');
    if(p >= 0) name.remove(p, name.size());

    return name;
}

auto to_seconds(const value& v)
{
    return src::seconds( static_cast<int64>(v.to_float()) );
}

auto to_time_point(const value& v)
{
    return src::time_point() + to_seconds(v);
}

}

////////////////////////////////////////////////////////////////////////////////
server::server(int port, QObject* parent) : QObject(parent)
{
    socket_.bind(port);
    connect(&socket_, &QUdpSocket::readyRead, this, &server::receive_data);
}

////////////////////////////////////////////////////////////////////////////////
void server::receive_data()
{
    while(socket_.hasPendingDatagrams())
    {
        auto data = socket_.receiveDatagram().data();
        osc::packet p(data.data(), data.size());

        try
        {
            auto e = p.parse();
            process(e);
        }
        catch(std::invalid_argument&)
        {
            // discard invalid packets
            // qDebug() << e.what();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void server::process(const element& e)
{
    if(e.is_bundle())
    {
        auto b = e.to_bundle();
        for(auto const& e : b.elements()) process(e);
    }
    else if(e.is_message())
    {
        auto m = e.to_message();
        process(m);
    }
}

////////////////////////////////////////////////////////////////////////////////
void server::process(const message& m)
{
    static std::regex re("/channel/([0-9]+)/stage/layer/([0-9]+)/foreground/file/(time|name)");
    std::smatch match;

    if(m.address() == "/event/state")
    {
        if(m.values().are<osc::string>())
        {
            auto state = m.value(0).to_string();
                 if(state == "start") emit event_start();
            else if(state == "stop" ) emit event_stop ();
            else if(state == "reset") emit event_reset();
        }
    }
    else if(std::regex_match(m.address(), match, re))
    {
        auto c = std::stoi(match[1]);
        auto l = std::stoi(match[2]);
        auto n = match[3];

        if(n == "name")
        {
            if(m.values().are<osc::string>() && channels_.count(c) && layers_.count(l))
            {
                if(auto name = to_name(m.values()[0]); name != videos_[pair(c, l)])
                {
                    // video name has changed, assume new video started playing
                    // and make its channel & layer active
                    channel_ = c;
                    layer_ = l;

                    videos_[pair(c, l)] = name;
                    emit video_name(name);
                }
            }
        }
        else if(n == "time")
        {
            if(m.values().are<float, float>())
            {
                auto time = to_time_point(m.values()[0]);
                auto total = to_seconds(m.values()[1]);

                if(c == channel_ && l == layer_)
                {
                    // active channel & layer
                    emit video_time(time, total);
                }
                else if(auto name = videos_.find(pair(c, l)); name != videos_.end())
                {
                    if(time == src::time_point())
                    {
                        // time reset to 0, assume same video started playing newly
                        // and make its channel & layer active
                        channel_ = c;
                        layer_ = l;

                        emit video_name(name->second);
                        emit video_time(time, total);
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
}
