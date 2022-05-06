//
// Created by dev on 5/6/22.
//

#include <manager/inc/draw_manager.h>
#include <manager/inc/scene_manager.h>

void DrawManager::draw_scene()
{

	canvas->clear();
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto camera = scene_manager->get_camera();
	DrawVisitor visitor(canvas, camera);
	visitor.visit(*scene);
}

