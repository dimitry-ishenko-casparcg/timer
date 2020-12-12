////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "time_widget.hpp"
#include <ctime>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
time_widget::time_widget(QWidget* parent) : QWidget(parent)
{
    ui_.setupUi(this);

    connect(ui_.hours, &label::clicked_up, this, &time_widget::hours_clicked_up);
    connect(ui_.hours, &label::clicked_down, this, &time_widget::hours_clicked_down);

    connect(ui_.minutes, &label::clicked_up, this, &time_widget::minutes_clicked_up);
    connect(ui_.minutes, &label::clicked_down, this, &time_widget::minutes_clicked_down);

    connect(ui_.seconds, &label::clicked_up, this, &time_widget::seconds_clicked_up);
    connect(ui_.seconds, &label::clicked_down, this, &time_widget::seconds_clicked_down);
}

////////////////////////////////////////////////////////////////////////////////
void time_widget::time(src::time_point tp)
{
    auto to_text = [](int n) { return QString::number(n).rightJustified(2, '0'); };

    auto time = src::system_clock::to_time_t(tp);
    auto tm = std::localtime(&time);

    ui_.hours  ->setText(to_text(tm->tm_hour));
    ui_.minutes->setText(to_text(tm->tm_min ));
    ui_.seconds->setText(to_text(tm->tm_sec ));
}

////////////////////////////////////////////////////////////////////////////////
void time_widget::update_sheet()
{
    QString sheet;

    if(fsize_ > 0) sheet += QString("font-size: %1pt;").arg(fsize_);
    if(fcolor_.isValid()) sheet += QString("color: %1;").arg(fcolor_.name());

    setStyleSheet(sheet);
}

////////////////////////////////////////////////////////////////////////////////
}
