//
// Created by dev on 5/7/22.
//

#ifndef INC_3_QT_CANVAS_FACTORY_H
#define INC_3_QT_CANVAS_FACTORY_H

#include <QGraphicsScene>
#include <memory>
#include "qt_canvas.h"

class QtCanvasFactory
{
public:
	explicit QtCanvasFactory(std::shared_ptr<QGraphicsScene> &scene);
	std::unique_ptr<Canvas> create();
private:
	std::shared_ptr<QGraphicsScene> scene{};
};



#endif //INC_3_QT_CANVAS_FACTORY_H
