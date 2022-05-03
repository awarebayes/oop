//
// Created by dev on 5/3/22.
//

#ifndef INC_3_TRANSFORM_MANAGER_H
#define INC_3_TRANSFORM_MANAGER_H
#include <utility>

#include "manager/inc/base_manager.h"
#include "object/inc/scene_object.h"

class TransformManager : public BaseManager
{
private:
	VisibleObject &transformable;
public:
	explicit TransformManager(VisibleObject &init) : transformable(init) {};
	TransformManager &rotate(float x, float y, float z);
	TransformManager &scale(float x, float y, float z);
	TransformManager &translate(float x, float y, float z);
};

#endif //INC_3_TRANSFORM_MANAGER_H
