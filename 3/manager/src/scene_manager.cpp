//
// Created by dev on 5/6/22.
//
#include "manager/inc/scene_manager.h"


SceneManager::SceneManager() : scene(std::make_shared<Scene>())
{}

std::shared_ptr<Scene> SceneManager::get_scene() const
{
	return scene;
}

void SceneManager::set_scene(const std::shared_ptr<Scene> &scene_)
{
	scene = scene_;
}

int SceneManager::add_object(const std::shared_ptr<ISceneObject> &object)
{
	return scene->add_object(object);
}

std::shared_ptr<ISceneObject> SceneManager::get_object(int obj_id)
{
	return scene->get_object(obj_id);
}

bool SceneManager::remove_object(int obj_id)
{
	return scene->remove_object(obj_id);
}

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
