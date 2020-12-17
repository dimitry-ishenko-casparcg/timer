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
event_widget::event_widget(QWidget* parent) : QWidget(parent)
{
    ui_.setupUi(this);
    reset();

    auto clock = src::clock::instance();
    connect(&*clock, &src::clock::time_changed, this, &event_widget::update);

    connect(ui_.widget, &time_widget::hours_clicked, [=](where w) { click(w, 1h); } );
    connect(ui_.widget, &time_widget::minutes_clicked, [=](where w) { click(w, 1min); } );
    connect(ui_.widget, &time_widget::seconds_clicked, [=](where w) { click(w, 1s); } );

    connect(ui_.widget, &time_widget::long_pressed, this, &event_widget::reset);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::font_size(double pt)
{
    ui_.widget->font_size(pt);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::name_font_size(double pt)
{
    ui_.name->setStyleSheet(QString("font-size: %1pt;").arg(pt));
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::start()
{
    start_ = src::clock::instance()->time();
    ui_.widget->font_color(Qt::white);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::stop()
{
    start_ = none;
    ui_.widget->font_color(Qt::gray);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::reset()
{
    std::tm tm { 0 /*sec*/, 0 /*min*/, 0 /*hr*/, 1 /*day*/, 1 /*mon*/, 0 /*year*/ };
    epoch_ = src::system_clock::from_time_t(std::mktime(&tm));

    stop();
    ui_.widget->time(epoch_);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::click(where w, src::seconds s)
{
    if(started())
    {
        switch(w)
        {
        case top: start_ -= s; break;
        case middle: stop(); break;
        case bottom: start_ += s; break;
        }
    }
    else if(w == middle) start();
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::update(src::time_point tp)
{
    if(started()) ui_.widget->time(epoch_ + (tp - start_));
}

////////////////////////////////////////////////////////////////////////////////
}
