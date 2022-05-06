//
// Created by dev on 5/3/22.
//

#ifndef INC_3_CAMERA_MANAGER_H
#define INC_3_CAMERA_MANAGER_H

#include <memory>
#include "base_manager.h"
#include "math/inc/linalg.h"

class CameraManager : public BaseManager
{
public:
	CameraManager() = default;
	~CameraManager() override = default;
	CameraManager(const CameraManager &) = delete;
	void move_to_point(const Vector<3> &point);
	void look_at(const Vector<3> &point);
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
