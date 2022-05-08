//
// Created by dev on 5/8/22.
//
#include "scene_meta.h"

void SceneMeta::add_object(int object_id, const std::string &meta)
{
	object_map[object_id] = meta;
	selected_object_id = object_id;
}

void SceneMeta::remove_object(int object_id)
{
	object_map.erase(object_map.find(object_id));
}

void SceneMeta::set_camera(int camera)
{
	active_camera = camera;
}

std::map<int, std::string> &SceneMeta::get_objects()
{
	return object_map;
}

int SceneMeta::get_selected()
{
	return selected_object_id;
}
