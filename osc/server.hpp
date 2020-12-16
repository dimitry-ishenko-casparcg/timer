////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_SERVER_HPP
#define OSC_SERVER_HPP

////////////////////////////////////////////////////////////////////////////////
#include "src/time.hpp"

#include <QObject>
#include <QString>
#include <QUdpSocket>

#include <osc++.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
/// OSC server.
///
/// Receives OSC messages, filters out the ones we might care about and does
/// basic pre-processing.
///
class server : public QObject
{
    Q_OBJECT

public:
    explicit server(int port, QObject* parent = nullptr);

signals:
    void event_start();
    void event_stop();
    void event_reset();

    void video_name(int channel, int layer, const QString&);
    void video_time(int channel, int layer, src::time_point, src::seconds);

private:
    QUdpSocket socket_;
    void receive_data();

    void process(const osc::element&);
    void process(const osc::message&);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
