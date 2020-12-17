////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_CUSTOM_HPP
#define GUI_CUSTOM_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QColor>
#include <QLabel>
#include <QString>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
namespace gui
{

////////////////////////////////////////////////////////////////////////////////
/// Custom widget.
///
/// Customizes base class Widget by adding functions to manipulate font size
/// and color through its style sheet.
///
template<typename Widget>
class custom : public Widget
{
public:
    using Widget::Widget;

    void font_size(double pt) { size_ = pt; update_sheet(); }
    void color(QColor c) { color_ = std::move(c); update_sheet(); }

private:
    double size_ = -1;
    QColor color_;

    void update_sheet()
    {
        QString sheet;

        if(size_ >= 0) sheet += QString("font-size: %1pt;").arg(size_);
        if(color_.isValid()) sheet += QString("color: %1;").arg(color_.name());

        Widget::setStyleSheet(sheet);
    }
};

////////////////////////////////////////////////////////////////////////////////
using custom_label = custom<QLabel>;
using custom_widget = custom<QWidget>;

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
