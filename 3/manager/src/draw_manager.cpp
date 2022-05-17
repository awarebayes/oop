//
// Created by dev on 5/7/22.
//


#include <drawer/inc/qt_canvas.h>
#include <manager/inc/draw_manager.h>
#include <visitor/inc/draw_visitor.h>
#include <manager/inc/manager_solution.h>

void DrawManager::draw_scene()
{
	if (not canvas)
		return;
	canvas->clear();
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto camera_manager = ManagerSolution::get_camera_manager();
	auto scene = scene_manager->get_scene();
	auto camera = camera_manager->get_active_camera();
	DrawVisitor visitor(canvas, camera);
	visitor.visit(*scene);
}

void DrawManager::set_canvas(std::shared_ptr<Canvas> &canvas_)
{
	canvas = canvas_;
}

std::shared_ptr<DrawManager> DrawManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}

void DrawManagerCreator::create()
{
	static auto manager = std::make_shared<DrawManager>();
	singleton = manager;
}


