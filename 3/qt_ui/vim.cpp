//
// Created by dev on 5/8/22.
//

#include "vim.h"

#include <utility>
#include <Qt>
#include <iostream>


Vim::Vim(std::function<void(const std::string& )> update_status_) : update_callback(std::move(update_status_))
{
	logic = std::make_shared<Logic>();
	logic->load_object("./objfiles/cube_processed.obj");
	logic->draw();
}


void Vim::handle_key(int key)
{
	if (key == Qt::Key_Escape)
		return go_to_normal();
	if (state_enum == VimStateEnum::Normal)
		return handle_key_in_normal(key);
	return state->handle_key(key);
}

void Vim::go_to_normal()
{
	state = std::make_unique<VimStateNormal>();
	state_enum = VimStateEnum::Normal;
	update_callback("<NORMAL>");
}

void Vim::handle_key_in_normal(int key)
{
	if (key == Qt::Key_O)
		return go_to_object();
	if (key == Qt::Key_C)
		return go_to_camera();
	if (key == Qt::Key_I)
		return logic->print_objects();
}

void Vim::go_to_object()
{
	state = std::make_unique<VimStateObject>(logic, update_callback);
	state_enum = VimStateEnum::Object;
}

void Vim::go_to_camera()
{
	state = std::make_unique<VimStateCamera>(logic, update_callback);
	state_enum = VimStateEnum::Camera;
}

VimStateObject::VimStateObject(std::shared_ptr<Logic> logic_, callback_t callback)
{
	logic = std::move(logic_);
	update_callback = std::move(callback);
	update_callback("<OBJECT>");
}

void VimStateObject::handle_key(int key)
{
	if (find_state)
		return handle_find(key);
	else if (key == Qt::Key_F)
		return start_find();
	else if (selected_object == -1)
		return update_callback("<OBJECT>: select object with F to edit it");
	else if (key == Qt::Key_W)
		return logic->move_selected_object(selected_object, 0, -10, 0);
	else if (key == Qt::Key_S)
		return logic->move_selected_object(selected_object, 0, 10, 0);
	else if (key == Qt::Key_A)
		return logic->move_selected_object(selected_object, -10, 0, 0);
	else if (key == Qt::Key_D)
		return logic->move_selected_object(selected_object, 10, 0, 0);
	else if (key == Qt::Key_E)
		return logic->move_selected_object(selected_object, 0, 0, 10);
	else if (key == Qt::Key_Q)
		return logic->move_selected_object(selected_object, 0, 0, -10);
	else if (key == Qt::Key_J)
		return logic->rotate_selected_object(selected_object, 10, 0, 0);
	else if (key == Qt::Key_K)
		return logic->rotate_selected_object(selected_object, -10, 0, 0);
	else if (key == Qt::Key_H)
		return logic->rotate_selected_object(selected_object, 0, -10, 0);
	else if (key == Qt::Key_L)
		return logic->rotate_selected_object(selected_object, 0, 10, 0);
}

void VimStateObject::handle_find(int key)
{
	find_state = true;
	if (key == Qt::Key_Return || key == Qt::Key_Enter)
	{
		int obj_id = std::atoi(find_str.c_str());
		if (logic->has_object_id(obj_id))
		{
			selected_object = obj_id;
			return reset_find_success();
		}
		return reset_find_fail();
	}
	else
	{
		char num = key - Qt::Key_0;
		if (num < 0 or num > 9)
			return reset_find_fail();
		find_str += ('0' + num);
		update_callback("<OBJECT->Find>: " + find_str);
	}
}

void VimStateObject::reset_find_fail()
{
	update_callback("<OBJECT->Find> !invalid id!: " + find_str);
	find_str = "";
	find_state = false;
}

void VimStateObject::reset_find_success()
{
	update_callback("<OBJECT->Find> selected object with id: " + find_str);
	find_str = "";
	find_state = false;
}

void VimStateObject::start_find()
{
	find_str = "";
	find_state = true;
	update_callback("<OBJECT->Find>: " + find_str);
}


VimStateCamera::VimStateCamera(std::shared_ptr<Logic> logic_, callback_t callback)
{
	logic = std::move(logic_);
	update_callback = std::move(callback);
	update_callback("<CAMERA>");
}
