//
// Created by dev on 5/3/22.
//

#ifndef INC_3_BASE_CANVAS_H
#define INC_3_BASE_CANVAS_H

class Canvas
{
public:
	Canvas() = default;
	virtual ~Canvas() = default;

	virtual void clear() = 0;
	virtual void draw_line(int x1, int y1, int x2, int y2) = 0;
};

#endif //INC_3_BASE_CANVAS_H
