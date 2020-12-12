////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "time_widget.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
namespace
{

auto to_text(int n) { return QString::number(n).rightJustified(2, '0'); }

}

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
void time_widget::time(const QTime& t)
{
    ui_.hours  ->setText(to_text(t.hour  ()));
    ui_.minutes->setText(to_text(t.minute()));
    ui_.seconds->setText(to_text(t.second()));
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
