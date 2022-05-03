//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_SCENE_H
#define INC_3_SCENE_H
#include <ordered_map>

class Scene
{
private:
	std::ordered_map<shared_ptr<SceneObject>> objects{};
public:
	int add_object(shared_ptr<SceneObject> object);
	void remove_object(shared_ptr<SceneObject> object);
};

#endif //INC_3_TEST_SCENE_H
