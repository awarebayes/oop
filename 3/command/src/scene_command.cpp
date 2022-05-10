//
// Created by dev on 5/7/22.
//

#include <command/inc/scene_command.h>
#include <manager/inc/test_draw_manager.h>
#include <manager/inc/draw_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/camera_manager.h>

void RenderSceneCommand::exec()
{
	auto draw_manager = DrawManagerCreator().get();
	draw_manager->draw_scene();
}

void SetActiveCameraSceneCommand::exec()
{
	auto scene_manager = SceneManagerCreator().get();
	auto camera_manager = CameraManagerCreator().get();
	auto cam = camera_manager->get_camera(cam_id);
	scene_manager->set_camera(cam);
}
