////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "clock_widget.hpp"
#include "src/clock.hpp"

using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
clock_widget::clock_widget(QWidget* parent) : time_widget(parent)
{
    color(Qt::red);

    auto clock = src::clock::instance();
    connect(&*clock, &src::clock::time_changed, this, &clock_widget::time);

    connect(this, &clock_widget::hours_clicked, [=](where w)
    {
             if(w == top) clock->add_delay(+1h);
        else if(w == bottom) clock->add_delay(-1h);
    });
    connect(this, &clock_widget::minutes_clicked, [=](where w)
    {
             if(w == top) clock->add_delay(+1min);
        else if(w == bottom) clock->add_delay(-1min);
    });
    connect(this, &clock_widget::seconds_clicked, [=](where w)
    {
             if(w == top) clock->add_delay(+1s);
        else if(w == bottom) clock->add_delay(-1s);
    });

    connect(this, &clock_widget::long_pressed, [=](){ clock->reset_delay(); });
}

////////////////////////////////////////////////////////////////////////////////
}
