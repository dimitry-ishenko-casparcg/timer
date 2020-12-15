////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "gui/main_window.hpp"

#include <QApplication>
#include <QFontDatabase>

#include <exception>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int exit_code = 0;
    try
    {
        QApplication app(argc, argv);
        QFontDatabase::addApplicationFont(":/seven.otf");

        int port = 7250;
        gui::mode mode = gui::windowed;

        // process options

        gui::main_window win(port, mode);
        win.show();

        exit_code = app.exec();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit_code = 1;
    }
    catch(...)
    {
        std::cerr << "???" << std::endl;
        exit_code = 1;
    }
    return exit_code;
}
