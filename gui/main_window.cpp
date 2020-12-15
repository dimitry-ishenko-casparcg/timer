////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "main_window.hpp"

#include <QApplication>
#include <QDesktopWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
main_window::main_window(int port, gui::mode mode, QWidget* parent) : QWidget(parent),
    server_(port)
{
    ui_.setupUi(this);

    if(mode == full_screen)
    {
        setWindowState(windowState() | Qt::WindowFullScreen);
        setGeometry(QApplication::desktop()->screenGeometry(this));
    }

    connect(&server_, &osc::server::event_start, ui_.event, &event_widget::start);
    connect(&server_, &osc::server::event_stop , ui_.event, &event_widget::stop );
    connect(&server_, &osc::server::event_reset, ui_.event, &event_widget::reset);
}

////////////////////////////////////////////////////////////////////////////////
}
