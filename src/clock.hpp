////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_CLOCK_HPP
#define SRC_CLOCK_HPP

////////////////////////////////////////////////////////////////////////////////
#include "time.hpp"

#include <QObject>
#include <QTimer>

#include <memory>

////////////////////////////////////////////////////////////////////////////////
namespace src
{

////////////////////////////////////////////////////////////////////////////////
/// Represents wall clock that emits current time.
///
class clock : public QObject
{
    Q_OBJECT

public:
    explicit clock(QObject* parent = nullptr);

    static std::shared_ptr<clock> instance();

signals:
    void time_changed(time_point);

private:
    QTimer timer_;
    void update_time();

    time_point time_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
