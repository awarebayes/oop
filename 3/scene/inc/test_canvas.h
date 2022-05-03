//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_CANVAS_H
#define INC_3_TEST_CANVAS_H

#include "canvas.h"
#include <vector>

class Line
{
public:
	int x1, y1, x2, y2;
	Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
};

class TestCanvas : public Canvas
{
private:
	std::vector<Line> lines;
public:
	void clear() override;
	void draw_line(int x1, int y1, int x2, int y2) override;
};

#endif //INC_3_TEST_CANVAS_H
