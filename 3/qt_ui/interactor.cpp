//
// Created by dev on 5/8/22.
//

#include "interactor.h"

#include <utility>
#include <Qt>
#include <iostream>
#include <sstream>


Interactor::Interactor(std::function<void(const std::string& )> update_status_) : update_callback(std::move(update_status_))
{
	logic = std::make_shared<Logic>();
	logic->load_object("./objfiles/cube_processed.obj");
	logic->new_camera();
	logic->draw();
}


void Interactor::handle_key(int key)
{
	if (selected_type == SelectedObjectType::VisibleObject)
		handle_key_with_vision_object(key);
	else if (selected_type == SelectedObjectType::Camera)
		handle_key_with_camera_object(key);
}

void Interactor::handle_key_with_vision_object(int key)
{
	if (selected_id == -1)
		return update_callback("<OBJECT>: select object with F to edit it");
	else if (key == Qt::Key_W)
		return logic->move_object(selected_id, 0, -10, 0);
	else if (key == Qt::Key_S)
		return logic->move_object(selected_id, 0, 10, 0);
	else if (key == Qt::Key_A)
		return logic->move_object(selected_id, -10, 0, 0);
	else if (key == Qt::Key_D)
		return logic->move_object(selected_id, 10, 0, 0);
	else if (key == Qt::Key_E)
		return logic->move_object(selected_id, 0, 0, 10);
	else if (key == Qt::Key_Q)
		return logic->move_object(selected_id, 0, 0, -10);
	else if (key == Qt::Key_J)
		return logic->rotate_object(selected_id, 10, 0, 0);
	else if (key == Qt::Key_K)
		return logic->rotate_object(selected_id, -10, 0, 0);
	else if (key == Qt::Key_H)
		return logic->rotate_object(selected_id, 0, -10, 0);
	else if (key == Qt::Key_L)
		return logic->rotate_object(selected_id, 0, 10, 0);
}

void Interactor::handle_key_with_camera_object(int key)
{
	if (key == Qt::Key_W)
		return logic->move_camera(selected_id, 0, -10, 0);
	else if (key == Qt::Key_S)
		return logic->move_camera(selected_id, 0, 10, 0);
	else if (key == Qt::Key_A)
		return logic->move_camera(selected_id, -10, 0, 0);
	else if (key == Qt::Key_D)
		return logic->move_camera(selected_id, 10, 0, 0);
	else if (key == Qt::Key_E)
		return logic->move_camera(selected_id, 0, 0, 10);
	else if (key == Qt::Key_Q)
		return logic->move_camera(selected_id, 0, 0, -10);
	else if (key == Qt::Key_J)
		return logic->rotate_camera(selected_id, 0, 10);
	else if (key == Qt::Key_K)
		return logic->rotate_camera(selected_id, 0, -10);
	else if (key == Qt::Key_H)
		return logic->rotate_camera(selected_id, 10, 0);
	else if (key == Qt::Key_L)
		return logic->rotate_camera(selected_id, -10, 0);
}

void Interactor::handle_command(const std::string &command)
{
	std::stringstream ss;
	ss.str(command);
	std::string command_type;
	ss >> command_type;
	if (command_type == "select")
		return handle_command_select(ss);
	if (command_type == "create")
		return handle_command_create(ss);
	if (command_type == "load")
		return handle_command_load(ss);
	if (command_type == "print")
		return update_callback(logic->print_objects());
	if (command_type == "help")
		return help();
	update_callback("unknown command! type 'help' to show list of available commands");
}


void Interactor::handle_command_select(std::stringstream &command)
{
	std::string obj_type;
	std::string obj_id;
	command >> obj_type;
	command >> obj_id;
	int obj_id_i = std::atoi(obj_id.c_str());
	if (obj_type == "object")
	{
		if (not logic->has_object_id(obj_id_i))
			return update_callback("Bad object id!");
		selected_id = obj_id_i;
		selected_type = SelectedObjectType::VisibleObject;
		update_callback("selected object: " + obj_id);
	}

	else if (obj_type == "camera")
	{
		if (not logic->has_camera_id(obj_id_i))
			return update_callback("Bad camera id!");
		selected_id = obj_id_i;
		selected_type = SelectedObjectType::Camera;
		update_callback("selected camera: " + obj_id);
		logic->draw();
		logic->set_active_camera(obj_id_i);
	}
	else
	{
		return update_callback("select [object, camera] <id>");
	}
}

void Interactor::help()
{
	update_callback("help - show help\n"
					"select [object, camera] <id>\n"
					"print - displays list of VisibleObject in scene\n");
}

void Interactor::handle_command_create(std::stringstream &command)
{
	std::string obj_type;
	command >> obj_type;
	if (obj_type == "camera")
	{
		int cam_id = logic->new_camera();
		update_callback("created and selected camera: " + std::to_string(cam_id));
		selected_id = cam_id;
		selected_type = SelectedObjectType::Camera;
		logic->draw();
		logic->set_active_camera(cam_id);
	}
	else
	{
		update_callback("Invalid command. Use 'create camera' to create a camera.");
	}
}

void Interactor::handle_command_load(std::stringstream &command)
{
	std::string obj_type;
	std::string path;
	command >> obj_type;
	command >> path;
	if (obj_type == "object" and not command.fail())
	{
		int obj_id = logic->load_object(path);
		update_callback("loaded an object from: " + path + " with id " + std::to_string(obj_id));
		logic->draw();
	}
	else
	{
		update_callback("Invalid command. Use 'load object <path>' to load an object.");
	}
}


