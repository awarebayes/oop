//
// Created by dev on 5/3/22.
//
#include <scene/inc/scene_group.h>

int SceneGroup::add_object(const std::shared_ptr<ISceneObject>& obj)
{
	objects[obj_count++] = obj;
	return obj_count-1;
}

bool SceneGroup::remove_object(int object_id)
{
	auto object_to_delete = objects.find(object_id);
	if (object_to_delete != objects.end())
	{
		objects.erase(object_to_delete);
		return true;
	}
	return false;
}

ObjectMap::const_iterator SceneGroup::begin()
{
	return objects.begin();
}

ObjectMap::const_iterator SceneGroup::end()
{
	return objects.end();
}

void SceneGroup::accept(Visitor &v)
{
	v.visit(*this);
}

std::shared_ptr<ISceneObject> SceneGroup::get_object(int object_id)
{
	return objects[object_id];
}

