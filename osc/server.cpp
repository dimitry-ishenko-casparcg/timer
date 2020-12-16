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

    auto const& val = m.values();
    if(m.address() == "/event/state")
    {
        if(val.size() == 1 && val[0].is_string())
        {
            auto state = val[0].to_string();
                 if(state == "start") emit event_start();
            else if(state == "stop" ) emit event_stop ();
            else if(state == "reset") emit event_reset();
        }
    }
    else if(std::regex_match(m.address(), match, re))
    {
        auto channel = std::stoi(match[1]);
        auto layer = std::stoi(match[2]);

        if(match[3] == "name")
        {
            if(val.size() == 1 && val[0].is_string())
            {
                QString name(val[0].to_string().data());
                emit video_name(channel, layer, name);
            }
        }
        else
        {
            if(val.size() == 2 && val[0].is_float() && val[1].is_float())
            {
                auto time = src::time_point() + src::seconds( static_cast<int64>(val[0].to_float()) );
                auto total = src::seconds( static_cast<int64>(val[1].to_float()) );

                emit video_time(channel, layer, time, total);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
}
