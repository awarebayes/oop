//
// Created by dev on 5/3/22.
//

#ifndef INC_3_TRANSFORM_MANAGER_H
#define INC_3_TRANSFORM_MANAGER_H
#include <utility>
#include <object/inc/mesh_model.h>

#include "manager/inc/base_manager.h"
#include "object/inc/scene_object.h"

class Transformer
{
private:
	ISceneObject &transformable;
public:
	explicit Transformer(ISceneObject &init) : transformable(init) {};
	Transformer &rotate(float x, float y, float z);
	Transformer &scale(float x, float y, float z);
	Transformer &translate(float x, float y, float z);
	Transformer &rotate_around_vertex(const Vertex &v, float x, float y, float z);
};

class TransformManager : public BaseManager
{
public:
	TransformManager() = default;
	~TransformManager() override = default;
	TransformManager(const TransformManager &) = delete;
	TransformManager &operator=(const TransformManager &) = delete;
	void move(int object_id, const Vector3 &param) const;
	void rotate(int object_id, const Vector3 &param) const;
	void scale(int object_id, const Vector3 &param) const;
};

class TransformManagerCreator
{
public:
	std::shared_ptr<TransformManager> get();
private:
	void create();
	std::shared_ptr<TransformManager> singleton;
};

#endif //INC_3_TRANSFORM_MANAGER_H
