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

    std::tm tm { };
    tm.tm_mday = 1; tm.tm_year = 100; tm.tm_isdst = -1;
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
    ui_.name->font_size(pt);
}

////////////////////////////////////////////////////////////////////////////////
void video_widget::start(const QString& name)
{
    ui_.name->color(Qt::white);
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
    ui_.name->color(dark_gray);
    ui_.widget->color(dark_gray);
}

////////////////////////////////////////////////////////////////////////////////
}
