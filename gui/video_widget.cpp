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
const QColor dark_gray(20, 20, 20);

////////////////////////////////////////////////////////////////////////////////
video_widget::video_widget(QWidget* parent) : QWidget(parent)
{
    ui_.setupUi(this);

    std::tm tm { 0 /*sec*/, 0 /*min*/, 0 /*hr*/, 1 /*day*/, 1 /*mon*/, 0 /*year*/ };
    epoch_ = src::system_clock::from_time_t(std::mktime(&tm));

    stop();
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
void video_widget::start(const QString& name)
{
    name_font_color(Qt::white);

    ui_.name->setText(name);
    ui_.widget->time(epoch_);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::time(src::time_point time, src::seconds total)
{
    ui_.widget->color(Qt::green);

    auto done = time.time_since_epoch();
    if(done > total) done = total;

    switch(mode_)
    {
    case count_up: ui_.widget->time(epoch_ + done); break;
    case count_down: ui_.widget->time(epoch_ + (total - done)); break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::stop()
{
    name_font_color(dark_gray);
    ui_.widget->color(dark_gray);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::name_font_color(const QColor& c)
{
    ui_.name->setStyleSheet(QString("color: %1;").arg(c.name()));
}

////////////////////////////////////////////////////////////////////////////////
}
