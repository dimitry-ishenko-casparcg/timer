////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "gui/main_window.hpp"

#include <QApplication>

#include <exception>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int exit_code = 0;
    try
    {
        QApplication app(argc, argv);

        gui::main_window win;
        win.show();

        // process options

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
