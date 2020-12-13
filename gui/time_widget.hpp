////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_TIME_WIDGET_HPP
#define GUI_TIME_WIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/time.hpp"
#include "ui_time_widget.h"

#include <QColor>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
/// A widget that shows time.
///
/// It forwards clicked_up and clicked_down signals from its children hours,
/// minutes and seconds.
///
class time_widget : public QWidget
{
    Q_OBJECT

public:
    explicit time_widget(QWidget* parent = nullptr);

    void font_size(double s) { fsize_ = s; update_sheet(); }
    void font_color(QColor c) { fcolor_ = std::move(c); update_sheet(); }

    void time(src::time_point);

signals:
    void hours_clicked_up();
    void hours_clicked_down();

    void minutes_clicked_up();
    void minutes_clicked_down();

    void seconds_clicked_up();
    void seconds_clicked_down();

    void long_pressed();

private:
    Ui::time_widget ui_;

    double fsize_ = -1;
    QColor fcolor_;

    void update_sheet();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
