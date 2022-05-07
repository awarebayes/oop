//
// Created by dev on 5/7/22.
//

#include "drawer/inc/qt_canvas_factory.h"

QtCanvasFactory::QtCanvasFactory(std::shared_ptr<QGraphicsScene> &scene_)
{
	scene = scene_;
}

std::unique_ptr<Canvas> QtCanvasFactory::create()
{
	return make_unique<QtCanvas>(scene);
}
