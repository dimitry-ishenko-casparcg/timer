////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "event_widget.hpp"
#include "src/clock.hpp"

#include <ctime>

using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
event_widget::event_widget(QWidget* parent) : time_widget(parent)
{
    reset();

    auto clock = src::clock::instance();
    connect(&*clock, &src::clock::time_changed, this, &event_widget::update);

    connect(this, &event_widget::hours_clicked, [=](where w) { click(w, 1h); } );
    connect(this, &event_widget::minutes_clicked, [=](where w) { click(w, 1min); } );
    connect(this, &event_widget::seconds_clicked, [=](where w) { click(w, 1s); } );

    connect(this, &event_widget::long_pressed, this, &event_widget::reset);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::start()
{
    start_ = src::clock::instance()->time();
    font_color(Qt::white);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::stop()
{
    start_ = none;
    font_color(Qt::gray);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::reset()
{
    stop();

    std::tm tm { 0 /*sec*/, 0 /*min*/, 0 /*hr*/, 1 /*day*/, 1 /*mon*/, 0 /*year*/ };
    epoch_ = src::system_clock::from_time_t(std::mktime(&tm));

    time(epoch_);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::click(where w, src::seconds s)
{
    if(started())
    {
        switch(w)
        {
        case top: epoch_ += s; break;
        case bottom: epoch_ -= s; break;
        case middle: stop(); break;
        }
    }
    else if(w == middle) start();
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::update(src::time_point tp)
{
    if(started()) time(epoch_ + (tp - start_));
}

////////////////////////////////////////////////////////////////////////////////
}
