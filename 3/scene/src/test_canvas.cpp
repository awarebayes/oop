//
// Created by dev on 5/1/22.
//

#include <scene/inc/test_canvas.h>

void TestCanvas::draw_line(int x1, int y1, int x2, int y2)
{
	lines.emplace_back(x1, y2, x2, y2);
}

void TestCanvas::clear()
{
	lines.clear();
}

