//
// Created by dev on 5/8/22.
//

#include <command/inc/camera_command.h>
#include <manager/inc/camera_manager.h>
#include <manager/inc/manager_solution.h>

CameraNewCommand::CameraNewCommand()
{

}

void CameraNewCommand::exec()
{
	auto manager = ManagerSolution::get_camera_manager();
 	camera_id = manager->new_camera();
}

int CameraNewCommand::get_result() const
{
	return camera_id;
}

void CameraMoveCommand::exec()
{
	auto c_manager = ManagerSolution::get_camera_manager();
	c_manager->offset_camera(camera_id, offset);
}

CameraMoveCommand::CameraMoveCommand(int camera_id_, const Vector3 &offset_)
{
	offset = offset_;
	camera_id = camera_id_;
}

CameraRotateCommand::CameraRotateCommand(int camera_id_, float x_offset_, float y_offset_)
{
	camera_id = camera_id_;
	x_offset = x_offset_;
	y_offset = y_offset_;
}

void CameraRotateCommand::exec()
{
	auto c_manager = ManagerSolution::get_camera_manager();
	c_manager->rotate_camera(camera_id, x_offset, y_offset);
}
