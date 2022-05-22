//
// Created by dev on 5/3/22.
//

#include <manager/inc/transform_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/manager_solution.h>
#include "math/inc/transformation.h"

Transformer &Transformer::rotate(float x, float y, float z)
{
	transformable.transform = std::make_shared<Transformation>(*transformable.transform + Rotation(x, y, z));
	return *this;
}

Transformer &Transformer::scale(float x, float y, float z)
{
	transformable.transform =std::make_shared<Transformation>(*transformable.transform + Scale(x, y, z));
	return *this;
}

Transformer &Transformer::translate(float x, float y, float z)
{

	transformable.transform =std::make_shared<Transformation>(*transformable.transform + Translation(x, y, z));
	return *this;
}

Transformer &Transformer::rotate_around_vertex(const Vertex &v, float x, float y, float z)
{
	throw std::runtime_error("Not implemented!");
}

void TransformManager::move(int object_id, const Vector3 &param) const
{
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).translate(param.x, param.y, param.z);
}

void TransformManager::rotate(int object_id, const Vector3 &param) const
{
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).rotate(param.x, param.y, param.z);
}

void TransformManager::scale(int object_id, const Vector3 &param) const
{
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).scale(param.x, param.y, param.z);
}

void TransformManagerCreator::create()
{
	static auto manager = std::make_shared<TransformManager>();
	singleton = manager;
}

std::shared_ptr<TransformManager> TransformManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}

