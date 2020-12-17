////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "gui/main_window.hpp"
#include "range.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFontDatabase>

#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

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
        "Set UDP port to listen on.\n"
        "Default: 7250\n",
        "n", "7250"
    },
    {
        "channel",
        "Set channel to be monitored. "
        "Default: 1\n",
        "...", "1"
    },
    {
        "layer",
        "Set one or more layers to be monitored. "
        "Layers can be specified as several comma-separated values and/or ranges. "
        "Negative numbers are removed from the set.\n"
        "This option can be repeated multiple times.\n"
        "Default: 10\n",
        "...", "10"
    },
    {
        "name-size",
        "Set font size for the event and video names.\n"
        "Default: 20\n",
        "pt", "20"
    },
    {
        "clock-size",
        "Set font size for the clock widget.\n"
        "Default: 160\n",
        "pt", "160"
    },
    {
        "event-size",
        "Set font size for the event widget.\n"
        "Default: 120\n",
        "pt", "120"
    },
    {
        "video-size",
        "Set font size for the video widget.\n"
        "Default: 160\n",
        "pt", "160"
    }});
    parser.addHelpOption();
}

////////////////////////////////////////////////////////////////////////////////
auto to_int(const QCommandLineParser& parser, const QString& opt)
{
    auto v = parser.value(opt);
    bool ok;
    auto n = v.toInt(&ok);

    if(!ok) throw std::invalid_argument(
        ("Invalid option '" + opt + "' value: " + v).toStdString()
    );
    return n;
}

////////////////////////////////////////////////////////////////////////////////
auto to_double(const QCommandLineParser& parser, const QString& opt)
{
    auto v = parser.value(opt);
    bool ok;
    auto n = v.toDouble(&ok);

    if(!ok) throw std::invalid_argument(
        ("Invalid option '" + opt + "' value: " + v).toStdString()
    );
    return n;
}

////////////////////////////////////////////////////////////////////////////////
auto collect(const QCommandLineParser& parser, const QString& opt)
{
    std::vector<range> ranges;
    std::vector<int> add, remove;

    bool ok;
    for(auto const& vv : parser.values(opt))
        for(auto const& v : vv.split(',', QString::SkipEmptyParts))
        {
            auto p = v.indexOf('-');
                 if(p == -1) add.push_back(v.toInt(&ok));
            else if(p ==  0) remove.push_back(-v.toInt(&ok));
            else
            {
                auto from = v.mid(0, p).toInt(&ok);
                auto to = v.mid(p+1).toInt(&ok);
                ranges.emplace_back(from, to);
            }

            if(!ok) throw std::invalid_argument(
                ("Invalid option '" + opt + "' value: " + v).toStdString()
            );
        }

    return std::tuple(ranges, add, remove);
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

        win.channel(to_int(parser, "channel"));

        // collect all --layer values
        auto [ranges, add, remove] = collect(parser, "layer");
        for(auto const& nn : ranges) win.add_layers(nn);
        for(auto n : add) win.add_layer(n);
        for(auto n : remove) win.remove_layer(n);

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
