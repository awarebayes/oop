//
// Created by dev on 5/3/22.
//

#include <manager/inc/transform_manager.h>
#include <manager/inc/scene_manager.h>
#include "math/inc/transformation.h"

Transformer &Transformer::rotate(float x, float y, float z)
{
	transformable._transform = CompositeTransformation(transformable._transform)
							 .compose(Rotation(x, y, z))
							 .share();
	return *this;
}

Transformer &Transformer::scale(float x, float y, float z)
{
	transformable._transform = CompositeTransformation(transformable._transform)
			.compose(Scale(x, y, z))
			.share();
	return *this;
}

Transformer &Transformer::translate(float x, float y, float z)
{

	transformable._transform = CompositeTransformation(transformable._transform)
			.compose(Translation(x, y, z))
			.share();
	return *this;
}

Transformer &Transformer::rotate_around_vertex(const Vertex &v, float x, float y, float z)
{
	transformable._transform = CompositeTransformation(transformable._transform)
			.compose(Translation(v(0), v(1), v(2)))
			.compose(Rotation(x, y, z))
			.compose(Translation(-v(0), -v(1), -v(2)))
			.share();
	return *this;
}

void TransformManager::move(int object_id, const Vector<3> &param) const
{
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).translate(param(0), param(1), param(2));
}

void TransformManager::rotate(int object_id, const Vector<3> &param) const
{
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).rotate(param(0), param(1), param(2));
}

void TransformManager::scale(int object_id, const Vector<3> &param) const
{
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto object = scene->get_object(object_id);
	Transformer(*object).scale(param(0), param(1), param(2));
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

