//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_CANVAS_CPP
#define INC_3_TEST_CANVAS_H

#include <vector>
#include "base_canvas.h"

class TestLine
{
public:
	int x1, y1, x2, y2;
	TestLine(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
};

bool operator==(const TestLine& lhs, const TestLine& rhs);


class TestCanvas : public ICanvas
{
public:
	std::vector<TestLine> lines;
	TestCanvas() = default;
	void clear() override;
	void draw_line(int x1, int y1, int x2, int y2) override;
};

#endif //INC_3_TEST_CANVAS_CPP
