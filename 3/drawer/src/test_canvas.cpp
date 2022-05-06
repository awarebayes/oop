//
// Created by dev on 5/1/22.
//

#include <drawer/inc/test_canvas.h>

void TestCanvas::draw_line(int x1, int y1, int x2, int y2)
{
	lines.emplace_back(x1, y1, x2, y2);
}

void TestCanvas::clear()
{
	lines.clear();
}

bool operator==(const TestLine& lhs, const TestLine& rhs)
{
	return lhs.x1 == rhs.x1 && lhs.y1 == rhs.y1 && lhs.x2 == rhs.x2 && lhs.y2 == rhs.y2;
}

