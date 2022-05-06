//
// Created by dev on 5/6/22.
//
#include "manager/inc/scene_manager.h"


SceneManager::SceneManager() : scene(std::make_shared<Scene>()) {}

std::shared_ptr<Scene> SceneManager::get_scene() const
{
	return scene;
}

void SceneManager::set_scene(const std::shared_ptr<Scene> &scene_)
{
	scene = scene_;
}

void SceneManager::set_camera(const std::shared_ptr<Camera> &camera_)
{
	camera = camera_;
}

std::shared_ptr<Camera> SceneManager::get_camera() const
{
	return camera;
};

void SceneManagerCreator::create()
{
	static auto manager = std::make_shared<SceneManager>();
	singleton = manager;
}

std::shared_ptr<SceneManager> SceneManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}
