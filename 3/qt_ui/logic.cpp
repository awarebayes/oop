//
// Created by dev on 5/8/22.
//

#include <memory>
#include <iostream>
#include <sstream>
#include "logic.h"

int Logic::load_object(const std::string &path)
{
	auto load_com = std::make_shared<LoadMeshCommand>(path);
	facade.exec(load_com);
	int result_id = load_com->get_result();
	meta.add_object(result_id, "Object loaded from: " + path);
	return result_id;
}

int Logic::new_camera()
{
	auto com = std::make_shared<CameraNewCommand>();
	facade.exec(com);
	int cam_id = com->get_result();
	meta.add_camera(cam_id);
	set_active_camera(cam_id);
	return cam_id;
}

void Logic::draw()
{
	auto com = std::make_shared<RenderSceneCommand>();
	facade.exec(com);
}

std::string Logic::print_objects()
{
	std::stringstream ss;
	ss << "Objects in scene\n";
	for (auto &[id, desc]: meta.get_objects())
	{
		ss << "Id: " << id << " | " << desc << "\n";
	}
	return ss.str();
}

void Logic::move_object(int object_id, float dx, float dy, float dz)
{
	auto offset = Vector3{dx, dy, dz};
	auto com = std::make_shared<ObjectMoveCommand>(object_id, offset);
	facade.exec(com);
	draw();
}

void Logic::rotate_object(int object_id, float dx, float dy, float dz)
{
	auto offset = Vector3{dx, dy, dz};
	auto com = std::make_shared<ObjectRotateCommand>(object_id, offset);
	facade.exec(com);
	draw();
}

bool Logic::has_object_id(int object_id)
{
	return meta.get_objects().find(object_id) != meta.get_objects().end();
}

bool Logic::has_camera_id(int camera_id)
{
	return meta.get_cameras().find(camera_id) != meta.get_cameras().end();
}

void Logic::set_active_camera(int camera_id)
{
	auto com = std::make_shared<SetActiveCameraSceneCommand>(camera_id);
	facade.exec(com);
	draw();
}

void Logic::move_camera(int camera_id, float dx, float dy, float dz)
{
	auto offset = Vector3{dx, dy, dz};
	auto com = std::make_shared<CameraMoveCommand>(camera_id, offset);
	facade.exec(com);
	draw();
}

void Logic::rotate_camera(int camera_id, float x_offset, float y_offset)
{
	auto com = std::make_shared<CameraRotateCommand>(camera_id, x_offset, y_offset);
	facade.exec(com);
	draw();
}

