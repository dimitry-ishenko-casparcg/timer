////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_MAIN_WINDOW_HPP
#define GUI_MAIN_WINDOW_HPP

////////////////////////////////////////////////////////////////////////////////
#include "osc/server.hpp"
#include "src/range.hpp"
#include "ui_main_window.h"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

enum window_mode
{
    windowed,
    full_screen,
};

////////////////////////////////////////////////////////////////////////////////
/// Main window widget.
///
class main_window : public QWidget
{
    Q_OBJECT

public:
    explicit main_window(int port, window_mode = windowed, QWidget* parent = nullptr);

    void channel(int n) { server_.channel(n); }

    void add_layer(int n) { server_.add_layer(n); }
    void add_layers(range nn) { server_.add_layers(nn); }
    void remove_layer(int n) { server_.remove_layer(n); }

    void name_size(double);
    void clock_size(double);
    void event_size(double);
    void video_size(double);

private:
    Ui::main_window ui_;
    osc::server server_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
