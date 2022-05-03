//
// Created by dev on 5/1/22.
//

#ifndef INC_3_DRAWABLE_MODEL_H
#define INC_3_DRAWABLE_MODEL_H

#include <memory>
#include "scene/inc/canvas.h"
#include "scene_object.h"
#include "math/inc/transformation.h"

class DrawableModel : public VisibleObject
{
private:
	std::unique_ptr<Transformation> transform;
public:
	virtual void draw(std::unique_ptr<Canvas> &canvas) const = 0;
};

#endif //INC_3_DRAWABLE_MODEL_H
