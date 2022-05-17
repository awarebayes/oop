//
// Created by dev on 5/3/22.
//

#ifndef INC_3_CAMERA_MANAGER_H
#define INC_3_CAMERA_MANAGER_H

#include <memory>
#include <object/inc/camera.h>
#include <map>
#include "base_manager.h"
#include "math/inc/linalg.h"

class CameraManager : public BaseManager
{
public:
	CameraManager() = default;
	~CameraManager() override = default;
	CameraManager(const CameraManager &) = delete;
	void offset_camera(int cam_id, const std::array<float, 3> &offset);
	void rotate_camera(int cam_id, float x_offset, float y_offset);
	void set_active_camera(int camera_id);
	std::shared_ptr<Camera> get_active_camera();
	int new_camera();
	std::shared_ptr<Camera> get_camera(int camera_id);
private:
	std::map<int, std::shared_ptr<Camera>> cams;
	std::shared_ptr<Camera> active_camera;
	int cam_count{};
};

class CameraManagerCreator
{
public:
	std::shared_ptr<CameraManager> get();
private:
	void create();
	std::shared_ptr<CameraManager> singleton;
};

#endif //INC_3_CAMERA_MANAGER_H
