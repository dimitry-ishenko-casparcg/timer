////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_CLOCK_WIDGET_HPP
#define GUI_CLOCK_WIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/time.hpp"
#include "time_widget.hpp"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
class clock_widget : public time_widget
{
    Q_OBJECT

public:
    explicit clock_widget(QWidget* parent = nullptr);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif