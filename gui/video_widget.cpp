////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "video_widget.hpp"
#include <QColor>
#include <ctime>

using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
const QColor dark_gray(42, 42, 42);

////////////////////////////////////////////////////////////////////////////////
video_widget::video_widget(QWidget* parent) : QWidget(parent)
{
    ui_.setupUi(this);

    std::tm tm { 0 /*sec*/, 0 /*min*/, 0 /*hr*/, 1 /*day*/, 1 /*mon*/, 0 /*year*/ };
    epoch_ = src::system_clock::from_time_t(std::mktime(&tm));

    reset();
    timer_.setInterval(3s);
    timer_.setSingleShot(true);
    connect(&timer_, &QTimer::timeout, this, &video_widget::reset);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::font_size(double pt)
{
    ui_.widget->font_size(pt);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::name_font_size(double pt)
{
    ui_.name->setStyleSheet(QString("font-size: %1pt;").arg(pt));
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::name(const QString& name)
{
    timer_.start();
    ui_.name->setText(name);
    color(Qt::white);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::time(src::time_point time, src::seconds total)
{
    if(time != time_)
    {
        timer_.start();
        time_ = time;

        auto done = time.time_since_epoch();
        if(done > total) done = total;

        switch(mode_)
        {
        case count_up: ui_.widget->time(epoch_ + done); break;
        case count_down: ui_.widget->time(epoch_ + (total - done)); break;
        }
        ui_.widget->font_color(Qt::green);
    }
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::color(const QColor& c)
{
    ui_.name->setStyleSheet(QString("color: %1;").arg(c.name()));
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::reset()
{
    timer_.stop();

    color(dark_gray);
    ui_.widget->font_color(dark_gray);
}

////////////////////////////////////////////////////////////////////////////////
}
