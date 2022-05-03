//
// Created by dev on 5/1/22.
//

#ifndef INC_3_SCENE_OBJECT_H
#define INC_3_SCENE_OBJECT_H
#include "math/inc/transformation.h"

class SceneObject
{
public:
	SceneObject() = default;
	virtual bool is_visible() = 0;
	virtual ~SceneObject() = default;
};

class VisibleObject : public SceneObject
{
private:
	std::unique_ptr<Transformation> transform{};
public:
	VisibleObject() = default;
	bool is_visible() override {return true;};
	~VisibleObject() override = default;
};

class InvisibleObject : public SceneObject
{
public:
	InvisibleObject() = default;
	bool is_visible() override {return false;};
	~InvisibleObject() override = default;
};

#endif //INC_3_SCENE_OBJECT_H
