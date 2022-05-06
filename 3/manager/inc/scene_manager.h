//
// Created by dev on 5/6/22.
//

#ifndef INC_3_SCENE_MANAGER_H
#define INC_3_SCENE_MANAGER_H

#include <scene/inc/scene.h>
#include "manager/inc/base_manager.h"

class SceneManager : public BaseManager
{
public:
	SceneManager();
	~SceneManager() override = default;
	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;
	[[nodiscard]] std::shared_ptr<Scene> get_scene() const;
	[[nodiscard]] std::shared_ptr<Camera> get_camera() const;
	void set_scene(const std::shared_ptr<Scene> &scene_);
	void set_camera(const std::shared_ptr<Camera> &camera );
private:
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Camera> camera;
};

class SceneManagerCreator
{
public:
	std::shared_ptr<SceneManager> get();
private:
	void create();
	std::shared_ptr<SceneManager> singleton;
};

#endif //INC_3_SCENE_MANAGER_H
