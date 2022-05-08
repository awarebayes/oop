//
// Created by dev on 5/8/22.
//

#include <memory>
#include <iostream>
#include "logic.h"

void Logic::load_object(const std::string &path)
{
	auto load_com = std::make_shared<LoadMeshCommand>(path);
	facade.exec(load_com);
	int result_id = load_com->get_result();
	meta.add_object(result_id, "Object loaded from: " + path);
}

void Logic::draw()
{
	auto com = std::make_shared<RenderSceneCommand>();
	facade.exec(com);
}

void Logic::print_objects()
{
	std::cout << "Objects in scene" << std::endl;
	for (auto &[id, desc]: meta.get_objects())
	{
		std::cout << "Id: " << id << " | " << desc << "\n";
	}
}

void Logic::move_selected_object(int object_id, float dx, float dy, float dz)
{
	auto offset = Vector<3>{dx, dy, dz};
	auto com = std::make_shared<ObjectMoveCommand>(object_id, offset);
	facade.exec(com);
	draw();
}

void Logic::rotate_selected_object(int object_id, float dx, float dy, float dz)
{
	auto offset = Vector<3>{dx, dy, dz};
	auto com = std::make_shared<ObjectRotateCommand>(object_id, offset);
	facade.exec(com);
	draw();
}

bool Logic::has_object_id(int object_id)
{
	return meta.get_objects().find(object_id) != meta.get_objects().end();
}

