////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_VIDEO_WIDGET_HPP
#define GUI_VIDEO_WIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/time.hpp"
#include "ui_video_widget.h"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
enum count_mode
{
    count_up,
    count_down
};


////////////////////////////////////////////////////////////////////////////////
class video_widget : public QWidget
{
    Q_OBJECT

public:
    explicit video_widget(QWidget* parent = nullptr);

    void font_size(double);
    void name_font_size(double);

    auto mode() const { return mode_; }
    void mode(count_mode mode) { mode_ = mode; }

    void start(const QString&);
    void time(src::time_point, src::seconds);
    void stop();

private:
    Ui::video_widget ui_;

    src::time_point epoch_;
    count_mode mode_ = count_down;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
