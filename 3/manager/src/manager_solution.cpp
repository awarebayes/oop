//
// Created by dev on 5/17/22.
//

#include <manager/inc/manager_solution.h>
#include <manager/inc/draw_manager.h>

std::shared_ptr <CameraManager> ManagerSolution::get_camera_manager()
{
	return CameraManagerCreator().get();
}

std::shared_ptr<LoadManager> ManagerSolution::get_load_manager()
{
	return LoadManagerCreator().get();
}

std::shared_ptr<SceneManager> ManagerSolution::get_scene_manager()
{
	return SceneManagerCreator().get();
}

std::shared_ptr<TransformManager> ManagerSolution::get_transform_manager()
{
	return TransformManagerCreator().get();
}

std::shared_ptr<DrawManager> ManagerSolution::get_draw_manager()
{
	return DrawManagerCreator().get();
}

