//
// Created by dev on 5/3/22.
//

#include <scene/inc/scene.h>
#include <object/inc/scene_object.h>
#include <object/inc/mesh_model.h>

int Scene::add_object(const std::shared_ptr<VisibleObject> &object)
{
	return visible_objects.add_object(object);
}

bool Scene::remove_object(int object_id)
{
	return visible_objects.remove_object(object_id);
}

std::shared_ptr<VisibleObject> Scene::get_object(int object_id)
{
	return visible_objects.get_object(object_id);
}

void Scene::accept(Visitor &v)
{
	visible_objects.accept(v);
}

int Scene::clone_object(int object_id)
{
	auto obj = visible_objects.get_object(object_id);
	if (not obj->is_mesh())
		throw std::runtime_error("object not clonable");
	std::shared_ptr<MeshModel> mesh = std::dynamic_pointer_cast<MeshModel>(obj);
	auto ref = std::make_shared<MeshModelReference>(mesh);
	return visible_objects.add_object(ref);
}


