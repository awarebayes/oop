//
// Created by dev on 5/6/22.
//

#include <manager/inc/test_draw_manager.h>
#include <manager/inc/scene_manager.h>
#include <drawer/inc/qt_canvas.h>
#include <drawer/inc/base_canvas.h>
#include <manager/inc/draw_manager.h>


void DrawManager::draw_scene()
{
	canvas->clear();
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto camera = scene_manager->get_camera();
	DrawVisitor visitor(canvas, camera);
	visitor.visit(*scene);
}

std::shared_ptr<DrawManager> DrawManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}

void DrawManagerCreator::create()
{
	static auto canvas = std::make_shared<Canvas>();
	static auto manager = std::make_shared<DrawManager>(canvas);
	singleton = manager;
}

std::shared_ptr<DrawManager> DrawManagerCreator::get_test()
{
	auto canvas = std::make_shared<Canvas>();
	return std::make_shared<DrawManager>(canvas);
}


