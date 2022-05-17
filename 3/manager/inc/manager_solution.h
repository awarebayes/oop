//
// Created by dev on 5/17/22.
//

#ifndef INC_3_MANAGER_SOLUTION_H
#define INC_3_MANAGER_SOLUTION_H

#include "camera_manager.h"
#include "load_manager.h"
#include "scene_manager.h"
#include "transform_manager.h"
#include <manager/inc/manager_solution.h>

enum class ManagerType
{
	CameraManager,
	LoadManager,
	SceneManager,
	TransformManager
};

class ManagerSolution
{
public:
	ManagerSolution() = delete;
	~ManagerSolution() = delete;
	ManagerSolution(ManagerSolution &) = delete;

	static std::shared_ptr<CameraManager> get_camera_manager();
	static std::shared_ptr<LoadManager> get_load_manager();
	static std::shared_ptr<SceneManager> get_scene_manager();
	static std::shared_ptr<TransformManager> get_transform_manager();
};

#endif //INC_3_MANAGER_SOLUTION_H
