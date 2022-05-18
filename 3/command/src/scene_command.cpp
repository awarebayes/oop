//
// Created by dev on 5/7/22.
//

#include <command/inc/scene_command.h>
#include <manager/inc/test_draw_manager.h>
#include <manager/inc/draw_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/camera_manager.h>
#include <manager/inc/manager_solution.h>

void RenderSceneCommand::exec()
{
	auto draw_manager = ManagerSolution::get_draw_manager();
	draw_manager->draw_scene();
}

void SetActiveCameraSceneCommand::exec()
{
	auto camera_manager = CameraManagerCreator().get();
	camera_manager->set_active_camera(cam_id);
}
