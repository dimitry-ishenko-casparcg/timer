////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "label.hpp"
#include <QMouseEvent>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
void label::mouseReleaseEvent(QMouseEvent* ev)
{
    if(ev->pos().y() < height() / 2) emit clicked_up();
    else emit clicked_down();
}

////////////////////////////////////////////////////////////////////////////////
}