//
// Created by dev on 5/7/22.
//

#ifndef INC_3_QT_CANVAS_H
#define INC_3_QT_CANVAS_H

#include <QGraphicsScene>
#include "drawer/inc/base_canvas.h"

class QtCanvas : public Canvas
{
public:
	QtCanvas() = delete;
	explicit QtCanvas(std::weak_ptr<QGraphicsScene> &scene_) : scene(scene_) {};
	void clear() override;
	void draw_line(int x1, int y1, int x2, int y2) override;
private:
	std::weak_ptr<QGraphicsScene> scene;
};

#endif //INC_3_QT_CANVAS_H
