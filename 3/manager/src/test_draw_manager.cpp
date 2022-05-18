//
// Created by dev on 5/6/22.
//

#include <manager/inc/test_draw_manager.h>
#include <manager/inc/scene_manager.h>
#include <drawer/inc/test_canvas.h>
#include <manager/inc/camera_manager.h>

void TestDrawManager::draw_scene()
{
	canvas->clear();
	auto scene_manager = SceneManagerCreator().get();
	auto camera_manager = CameraManagerCreator().get();
	auto camera = camera_manager->get_active_camera();
	auto scene = scene_manager->get_scene();
	DrawVisitor visitor(canvas, camera);
	visitor.visit(*scene);
}

std::shared_ptr<TestDrawManager> TestDrawManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}

void TestDrawManagerCreator::create()
{
	static auto canvas = std::make_shared<TestCanvas>();
	static auto manager = std::make_shared<TestDrawManager>(canvas);
	singleton = manager;
}

std::shared_ptr<TestDrawManager> TestDrawManagerCreator::get_test()
{
	auto canvas = std::make_shared<TestCanvas>();
	return std::make_shared<TestDrawManager>(canvas);
}
