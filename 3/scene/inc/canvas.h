//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CANVAS_H
#define INC_3_CANVAS_H

class Canvas
{
public:
	virtual void clear() = 0;
	virtual void draw_line(int x1, int y1, int x2, int y2) = 0;
	Canvas() = default;
	virtual ~Canvas() = default;
};

#endif //INC_3_CANVAS_H
