////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"
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

    timer_.setInterval(100 /*ms*/);
    timer_.start();
    connect(&timer_, &QTimer::timeout, this, &server::update);
}

////////////////////////////////////////////////////////////////////////////////
void server::receive_data()
{
    while(socket_.hasPendingDatagrams())
    {
        osc::packet p(socket_.pendingDatagramSize());
        socket_.readDatagram(p.data(), p.size());

        try
        {
            auto e = p.parse();
            process(e);
        }
        catch(std::invalid_argument&)
        {
            // discard invalid packet
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
    static std::regex re("/channel/([0-9]+)/stage/layer/([0-9]+)(/foreground)?/file/(path|time)");
    std::smatch match;

    if(m.address() == "/event/state")
    {
        if(m.values().are<osc::string>())
        {
            auto state = m.value(0).to_string();
                 if(state == "start" ) emit event_start ();
            else if(state == "pause" ) emit event_pause ();
            else if(state == "resume") emit event_resume();
            else if(state == "stop"  ) emit event_stop  ();
            else if(state == "reset" ) emit event_reset ();
        }
    }
    else if(std::regex_match(m.address(), match, re))
    {
        auto channel = std::stoi(match[1]);
        auto layer = std::stoi(match[2]);
        auto type = match[4];

        if(type == "path")
        {
            // compare in increasing order of complexity
            if(channel == channel_ && m.values().are<osc::string>() && layers_.count(layer))
            {
                auto name = to_name(m.value(0));
                auto& video = video_[layer];

                if(name != video.name)
                {
                    video.name = name;
                    video.total = 0s;
                }
                video.when = src::system_clock::now();
            }
        }
        else if(type == "time")
        {
            // compare in increasing order of complexity
            if(channel == channel_ && m.values().are<float, float>())
            {
                if(auto vi = video_.find(layer); vi != video_.end())
                {
                    vi->second.time = to_time_point(m.value(0));
                    vi->second.total = to_seconds(m.value(1));

                    vi->second.when = src::system_clock::now();
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void server::update()
{
    auto now = src::system_clock::now();

    int layer = -1;
    video_data video; video.total = 0s;

    // get top active video
    for(auto vi = video_.rbegin(); vi != video_.rend(); ++vi)
    {
        auto const& [l, v] = *vi;
        if(now - v.when < 3s)
        {
            layer = l;
            video = v;
            break;
        }
    }

    if(layer != layer_ || video.name != name_)
    {
        emit video_stop();

        layer_ = layer;
        name_ = video.name;

        if(name_.size()) emit video_start(name_);
    }

    if(video.total > 0s) emit video_time(video.time, video.total);
}

////////////////////////////////////////////////////////////////////////////////
}
