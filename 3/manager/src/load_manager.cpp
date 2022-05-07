//
// Created by dev on 5/7/22.
//

#include <manager/inc/load_manager.h>
#include <string>
#include <manager/inc/scene_manager.h>
#include <load/inc/mesh_model_loader.h>


int LoadManager::load_mesh_model(const std::string &path)
{
	auto scene_manager = SceneManagerCreator().get();
	auto scene = scene_manager->get_scene();
	auto model = MeshModelLoader().load_model(path);
	return scene->add_object(model);
}

void LoadManagerCreator::create()
{
	static auto manager = std::make_shared<LoadManager>();
	singleton = manager;
}

std::shared_ptr<LoadManager> LoadManagerCreator::get()
{
	if (not singleton) create();
	return singleton;
}
