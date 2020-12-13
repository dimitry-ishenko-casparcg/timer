////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "clock_widget.hpp"
#include "src/clock.hpp"

#include <QTimer>

using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
clock_widget::clock_widget(QWidget* parent) : time_widget(parent)
{
    font_color(Qt::red);

    auto clock = src::clock::instance();
    connect(&*clock, &src::clock::time_changed, this, &clock_widget::time);

    connect(this, &clock_widget::hours_clicked_up, [=](){ clock->add_delay(+1h); });
    connect(this, &clock_widget::hours_clicked_down, [=](){ clock->add_delay(-1h); });

    connect(this, &clock_widget::minutes_clicked_up, [=](){ clock->add_delay(+1min); });
    connect(this, &clock_widget::minutes_clicked_down, [=](){ clock->add_delay(-1min); });

    connect(this, &clock_widget::seconds_clicked_up, [=](){ clock->add_delay(+1s); });
    connect(this, &clock_widget::seconds_clicked_down, [=](){ clock->add_delay(-1s); });

    connect(this, &clock_widget::long_pressed, [=](){ clock->reset_delay(); });
}

////////////////////////////////////////////////////////////////////////////////
}
