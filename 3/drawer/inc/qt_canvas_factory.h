//
// Created by dev on 5/7/22.
//

#ifndef INC_3_QT_CANVAS_FACTORY_H
#define INC_3_QT_CANVAS_FACTORY_H

#include <QGraphicsScene>
#include <memory>
#include "qt_canvas.h"
#include "canvas_factory.h"

class QtCanvasFactory : public CanvasFactory
{
public:
	explicit QtCanvasFactory(std::weak_ptr<QGraphicsScene> scene);
	std::unique_ptr<Canvas> create() override;
private:
	std::weak_ptr<QGraphicsScene> scene{};
};



#endif //INC_3_QT_CANVAS_FACTORY_H
