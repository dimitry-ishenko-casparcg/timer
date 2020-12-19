////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
clock::clock(QObject* parent) : QObject(parent)
{
    connect(&timer_, &QTimer::timeout, this, &clock::update_time);

    timer_.setInterval(100 /*ms*/);
    timer_.start();
}

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<clock> clock::instance()
{
    static auto clock_ = std::make_shared<clock>();
    return clock_;
}

////////////////////////////////////////////////////////////////////////////////
void clock::update_time()
{
    auto now = system_clock::now();
    auto sec = duration_cast<seconds>(now.time_since_epoch());

    time_ = time_point(sec) + delay_;
    emit time_changed(time_);
}

////////////////////////////////////////////////////////////////////////////////
}
