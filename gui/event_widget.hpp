////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_EVENT_WIDGET_HPP
#define GUI_EVENT_WIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/time.hpp"
#include "ui_event_widget.h"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
class event_widget : public QWidget
{
    Q_OBJECT

public:
    explicit event_widget(QWidget* parent = nullptr);

    void font_size(double);
    void name_font_size(double);

    void start();
    void pause();
    void resume();
    void stop();
    void reset();

    bool started() const { return start_ != none; }
    bool paused() const { return pause_ != none; }

private:
    Ui::event_widget ui_;

    static constexpr auto none = src::time_point::min();
    src::time_point epoch_, start_, pause_;

    void click(where, src::seconds);

    void update(src::time_point);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
