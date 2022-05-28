//
// Created by dev on 5/7/22.
//

#ifndef INC_3_CANVAS_FACTORY_H
#define INC_3_CANVAS_FACTORY_H

class CanvasFactory
{
public:
	CanvasFactory() = default;
	virtual ~CanvasFactory() = default;
	virtual std::unique_ptr<ICanvas> create() = 0;
};

#endif //INC_3_CANVAS_FACTORY_H
