////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_SERVER_HPP
#define OSC_SERVER_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/range.hpp"
#include "src/time.hpp"

#include <QObject>
#include <QString>
#include <QUdpSocket>

#include <osc++.hpp>

#include <map>
#include <set>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
/// OSC server.
///
/// Receives OSC messages, filters out the ones we care about and does
/// basic pre-processing.
///
/// Specifically, the server keeps track of which is video is played on which
/// channel and layer and only signals name and time for the latest video.
///
class server : public QObject
{
    Q_OBJECT

public:
    explicit server(int port, QObject* parent = nullptr);

    void channel(int n) { channel_ = n; }

    void add_layer(int n) { layers_.insert(n); }
    void add_layers(range nn) { layers_.insert(nn.begin(), nn.end()); }

    void remove_layer(int n) { layers_.erase(n); }

signals:
    void event_start();
    void event_stop();
    void event_reset();

    void video_name(const QString&);
    void video_time(src::time_point, src::seconds);

private:
    QUdpSocket socket_;
    void receive_data();

    void process(const osc::element&);
    void process(const osc::message&);

    int channel_ = -1; // monitored channel
    std::set<int> layers_; // monitored layers

    int layer_ = -1; // active layer

    std::map<int, QString> videos_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
