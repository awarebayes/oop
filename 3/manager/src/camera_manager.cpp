//
// Created by dev on 5/6/22.
//

#include <manager/inc/camera_manager.h>
#include <manager/inc/scene_manager.h>

void CameraManager::move_to_point(const Vector<3> &point)
{
	auto scene_manager = SceneManagerCreator().get();
	auto cam = scene_manager->get_camera();
}

void CameraManager::look_at(const Vector<3> &point)
{
	auto scene_manager = SceneManagerCreator().get();
	auto cam = scene_manager->get_camera();
}

void CameraManagerCreator::create()
{
	static auto manager = std::make_shared<CameraManager>();
	singleton = manager;
}

std::shared_ptr<CameraManager> CameraManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}
