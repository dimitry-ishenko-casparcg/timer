////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"

#include <QDebug>
#include <QNetworkDatagram>

#include <osc++.hpp>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
server::server(int port, QObject* parent) : QObject(parent)
{
    socket_.bind(port);
    connect(&socket_, &QUdpSocket::readyRead, this, &server::receive_data);
}

////////////////////////////////////////////////////////////////////////////////
void server::receive_data()
{
    while(socket_.hasPendingDatagrams())
    {
        auto data = socket_.receiveDatagram().data();
        osc::packet p(data.data(), data.size());

        try
        {
            auto e = p.parse();
            process(e);
        }
        catch(std::invalid_argument&)
        {
            // discard invalid packets
            // qDebug() << e.what();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void server::process(const element& e)
{
    if(e.is_bundle())
    {
        auto b = e.to_bundle();
        for(auto const& e : b.elements()) process(e);
    }
    else if(e.is_message())
    {
        auto m = e.to_message();
        process(m);
    }
}

////////////////////////////////////////////////////////////////////////////////
void server::process(const message&)
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////
}
