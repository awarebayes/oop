//
// Created by dev on 5/7/22.
//

#include "drawer/inc/qt_canvas_factory.h"

QtCanvasFactory::QtCanvasFactory(std::shared_ptr<QGraphicsScene> &scene_)
{
	scene = scene_;
}

std::shared_ptr<Canvas> QtCanvasFactory::create()
{
	return std::make_shared<QtCanvas>(scene);
}
