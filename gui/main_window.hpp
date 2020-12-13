////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_MAIN_WINDOW_HPP
#define GUI_MAIN_WINDOW_HPP

////////////////////////////////////////////////////////////////////////////////
#include "ui_main_window.h"
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

enum mode
{
    windowed,
    full_screen,
};

////////////////////////////////////////////////////////////////////////////////
class main_window : public QWidget
{
    Q_OBJECT

public:
    explicit main_window(gui::mode = windowed, QWidget* parent = nullptr);

private:
    Ui::main_window ui_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
