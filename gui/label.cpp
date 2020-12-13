////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "label.hpp"
#include <QMouseEvent>

using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
label::label(QWidget* parent) : QLabel(parent)
{
    timer_.setSingleShot(true);
    timer_.setInterval(1500ms);

    connect(&timer_, &QTimer::timeout, this, &label::long_pressed);
}

////////////////////////////////////////////////////////////////////////////////
void label::mousePressEvent(QMouseEvent* ev)
{
    timer_.start();
    QLabel::mousePressEvent(ev);
}

////////////////////////////////////////////////////////////////////////////////
void label::mouseReleaseEvent(QMouseEvent* ev)
{
    if(timer_.isActive())
    {
        timer_.stop();

             if(ev->pos().y() <= height() * 1/4) emit clicked(top);
        else if(ev->pos().y() >= height() * 3/4) emit clicked(bottom);
        else emit clicked(middle);
    }

    QLabel::mouseReleaseEvent(ev);
}

////////////////////////////////////////////////////////////////////////////////
}
