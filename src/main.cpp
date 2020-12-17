////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "gui/main_window.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFontDatabase>

#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
void add_options(QCommandLineParser& parser)
{
    parser.addOptions({
    {
        "full-screen",
        "Show application in full screen.\n"
    },
    {
        "port",
        "Set UDP port to listen on.\n",
        "n", "7205"
    },
    {
        "channel",
        "Set one or more channels to be monitored. "
        "Channels can be specified as several comma-separated values and/or ranges. "
        "Negative numbers are removed from the set.\n"
        "This option can be repeated multiple times.\n",
        "...", "1"
    },
    {
        "layer",
        "Set one or more layers to be monitored. "
        "Layers can be specified as several comma-separated values and/or ranges. "
        "Negative numbers are removed from the set.\n"
        "This option can be repeated multiple times.\n",
        "...", "10"
    },
    {
        "name-size",
        "Set font size for the event and video names.\n",
        "pt", "20"
    },
    {
        "clock-size",
        "Set font size for the clock widget.\n",
        "pt", "160"
    },
    {
        "event-size",
        "Set font size for the event widget.\n",
        "pt", "120"
    },
    {
        "video-size",
        "Set font size for the video widget.\n",
        "pt", "160"
    }});
    parser.addHelpOption();
}

////////////////////////////////////////////////////////////////////////////////
auto to_int(const QCommandLineParser& parser, const QString& option)
{
    auto value = parser.value(option);
    bool ok;
    auto n = value.toInt(&ok);

    if(!ok) throw std::invalid_argument(
        ("Invalid '" + option + "' value: " + value).toStdString()
    );
    return n;
}

////////////////////////////////////////////////////////////////////////////////
auto to_double(const QCommandLineParser& parser, const QString& option)
{
    auto value = parser.value(option);
    bool ok;
    auto n = value.toDouble(&ok);

    if(!ok) throw std::invalid_argument(
        ("Invalid '" + option + "' value: " + value).toStdString()
    );
    return n;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int exit_code = 0;
    try
    {
        QApplication app(argc, argv);
        QFontDatabase::addApplicationFont(":/seven.otf");

        QCommandLineParser parser;
        add_options(parser);
        parser.process(app);

        auto port = to_int(parser, "port");
        auto mode = parser.isSet("full-screen") ? gui::full_screen : gui::windowed;

        gui::main_window win(port, mode);
        win.show();

        // channels & layers

        win. name_size(to_double(parser,  "name-size"));
        win.clock_size(to_double(parser, "clock-size"));
        win.event_size(to_double(parser, "event-size"));
        win.video_size(to_double(parser, "video-size"));

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
