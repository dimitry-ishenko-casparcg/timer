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

    std::tm tm { };
    tm.tm_mday = 1; tm.tm_year = 100; tm.tm_isdst = -1;
    epoch_ = src::system_clock::from_time_t(std::mktime(&tm));

    auto clock = src::clock::instance();
    connect(&*clock, &src::clock::time_changed, this, &event_widget::update);

    connect(ui_.widget, &time_widget::hours_clicked, [=](where w) { click(w, 1h); } );
    connect(ui_.widget, &time_widget::minutes_clicked, [=](where w) { click(w, 1min); } );
    connect(ui_.widget, &time_widget::seconds_clicked, [=](where w) { click(w, 1s); } );

    connect(ui_.widget, &time_widget::long_pressed, this, &event_widget::reset);

    reset();
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
    pause_ = none;
    ui_.widget->color(Qt::white);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::pause()
{
    if(started() && !paused()) pause_ = src::clock::instance()->time();
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::resume()
{
    if(paused())
    {
        start_ = src::clock::instance()->time() + (start_ - pause_);
        pause_ = none;
    }
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::stop()
{
    start_ = pause_ = none;
    ui_.widget->color(Qt::gray);
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::reset()
{
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
        case middle: if(paused()) resume(); else pause(); break;
        case bottom: start_ += s; break;
        }
    }
    else if(w == middle) start();
}

////////////////////////////////////////////////////////////////////////////////
void event_widget::update(src::time_point tp)
{
    if(started())
    {
        if(paused()) tp = pause_;
        ui_.widget->time(epoch_ + (tp - start_));
    }
}

////////////////////////////////////////////////////////////////////////////////
}
