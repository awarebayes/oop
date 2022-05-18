//
// Created by dev on 5/7/22.
//
#include <manager/inc/transform_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/manager_solution.h>
#include "command/inc/object_command.h"

ObjectMoveCommand::ObjectMoveCommand(int object_id_, const Vector<3> &offset_)
{
	offset = offset_;
	object_id = object_id_;
}

void ObjectMoveCommand::exec()
{
	auto t_manager = ManagerSolution::get_transform_manager();
	t_manager->move(object_id, offset);
}

ObjectScaleCommand::ObjectScaleCommand(int object_id_, const Vector<3> &offset_)
{
	scale = offset_;
	object_id = object_id_;
}

void ObjectScaleCommand::exec()
{
	auto t_manager = ManagerSolution::get_transform_manager();
	t_manager->scale(object_id, scale);
}

ObjectRotateCommand::ObjectRotateCommand(int object_id_, const Vector<3> &offset_)
{

	rotation = offset_;
	object_id = object_id_;
}

void ObjectRotateCommand::exec()
{
	auto t_manager = ManagerSolution::get_transform_manager();
	t_manager->rotate(object_id, rotation);
}

ObjectDeleteCommand::ObjectDeleteCommand(int object_id_)
{
	object_id = object_id_;
}

void ObjectDeleteCommand::exec()
{
	auto s_manager = ManagerSolution::get_scene_manager();
	succ = s_manager->remove_object(object_id);
}

bool ObjectDeleteCommand::get_result() const
{
	return succ;
}
