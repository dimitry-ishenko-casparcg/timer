////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"

#include <QNetworkDatagram>
#include <osc++.hpp>

#include <regex>
#include <stdexcept>
#include <string> // std::stoi

using namespace std::chrono_literals;

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

    return name.toUpper();
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
    static std::regex re("/channel/([0-9]+)/stage/layer/([0-9]+)/foreground/file/(path|time)");
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

        if(n == "path")
        {
            // compare in increasing order of complexity
            if(c == channel_ && m.values().are<osc::string>() && layers_.count(l))
            {
                auto name = to_name(m.value(0));
                auto& video = video_[l];

                if(name != video.name)
                {
                    video.name = name;
                    video.time = src::time_point();
                    video.total= src::seconds();
                    video.when = src::system_clock::now();
                }
            }
        }
        else if(n == "time")
        {
            // compare in increasing order of complexity
            if(c == channel_ && m.values().are<float, float>())
            {
                if(auto vi = video_.find(l); vi != video_.end())
                {
                    auto time = to_time_point(m.value(0));
                    auto total = to_seconds(m.value(1));

                    vi->second.time = time;
                    vi->second.total = total;
                    vi->second.when = src::system_clock::now();
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
}
