//
// Created by dev on 5/7/22.
//



#include <drawer/inc/qt_canvas.h>

void QtCanvas::draw_line(int x1, int y1, int x2, int y2)
{
	scene.lock()->addLine(x1, y1, x2, y2);
}

void QtCanvas::clear()
{
	scene.lock()->clear();
}
