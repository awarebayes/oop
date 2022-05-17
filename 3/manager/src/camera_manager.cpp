//
// Created by dev on 5/6/22.
//

#include <manager/inc/camera_manager.h>
#include <manager/inc/scene_manager.h>

void CameraManager::set_active_camera(int camera_id)
{
	auto cam = cams[camera_id];
	active_camera = cam;
}

int CameraManager::new_camera()
{
	// cam_count++;ad
	auto camera = std::make_shared<FPSCamera>(Vector3{0, 0, -100});
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto camera_id = scene->add_object(camera);
	cams[camera_id] = camera;
	return camera_id;
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

std::shared_ptr<Camera> CameraManager::get_active_camera()
{
	return active_camera;
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
