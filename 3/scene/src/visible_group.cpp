//
// Created by dev on 5/3/22.
//
#include <scene/inc/visible_group.h>

int VisibleGroup::add_object(const std::shared_ptr<VisibleObject>& obj)
{
	objects[obj_count++] = obj;
	return obj_count-1;
}

bool VisibleGroup::remove_object(int object_id)
{
	auto object_to_delete = objects.find(object_id);
	if (object_to_delete != objects.end())
	{
		objects.erase(object_to_delete);
		return true;
	}
	return false;
}

std::map<int, std::shared_ptr<VisibleObject>>::iterator VisibleGroup::begin()
{
	return objects.begin();
}

std::map<int, std::shared_ptr<VisibleObject>>::iterator VisibleGroup::end()
{
	return objects.end();
}

void VisibleGroup::accept(Visitor &v)
{
	v.visit(*this);
}

std::shared_ptr<VisibleObject> VisibleGroup::get_object(int object_id)
{
	return objects[object_id];
}

