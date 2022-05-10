//
// Created by dev on 5/6/22.
//

#include <manager/inc/camera_manager.h>
#include <manager/inc/scene_manager.h>

void CameraManager::set_active_camera(int camera_id)
{
	auto cam = cams[camera_id];
	auto scene_manager = SceneManagerCreator().get();
	scene_manager->set_camera(cam);
}

int CameraManager::new_camera()
{
	cams[cam_count++] = std::make_shared<FPSCamera>(glm::vec3{0, 0, -100});
	return cam_count - 1;
}

std::shared_ptr<Camera> CameraManager::get_camera(int camera_id)
{
	return cams[camera_id];
}

void CameraManager::rotate_camera(int cam_id, float x_offset, float y_offset)
{
	auto cam = cams[cam_id];
	cam->rotate(x_offset, y_offset);
}

void CameraManager::offset_camera(int cam_id, const std::array<float, 3> &offset)
{
	auto cam = cams[cam_id];
	cam->move({offset[0], offset[1], offset[2]});
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
