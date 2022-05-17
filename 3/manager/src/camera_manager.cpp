//
// Created by dev on 5/6/22.
//

#include <manager/inc/camera_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/manager_solution.h>
#include <exception/logic_exceptions.h>

void CameraManager::set_active_camera(int camera_id)
{
	auto cam = cams[camera_id];
	active_camera = cam;
}

int CameraManager::new_camera()
{
	auto camera = CameraFactory::create(CameraType::FPS);
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto camera_id = scene_manager->add_object(camera);
	cams[camera_id] = camera;
	return camera_id;
}

std::shared_ptr<ICamera> CameraManager::get_camera(int camera_id)
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

std::shared_ptr<ICamera> CameraManager::get_active_camera()
{
	return active_camera;
}

bool CameraManager::delete_camera(int camera_id)
{
	auto scene_manager = ManagerSolution::get_scene_manager();
	auto cam_it = cams.find(camera_id);
	if (cam_it == cams.end())
		return false;
	if (cams.size() == 1)
		throw LastCameraRemoveError(__FILE__, __LINE__, "Cannot remove the last camera");
	cams.erase(cam_it);
	return scene_manager->remove_object(camera_id);
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
