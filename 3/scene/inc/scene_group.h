//
// Created by dev on 5/3/22.
//

#ifndef INC_3_SCENE_GROUP_H
#define INC_3_SCENE_GROUP_H
#include "object/inc/scene_object.h"
#include <map>

class SceneGroup : public ISceneObject
{
	ObjectMap objects{};
	int obj_count = 0;
public:
	SceneGroup() = default;
	~SceneGroup() override = default;

	bool is_grouped() override {return true;};
	int add_object(const std::shared_ptr<ISceneObject>& obj);
	bool remove_object(int object_id);
	std::shared_ptr<ISceneObject> get_object(int object_id);
	ObjectMap::const_iterator begin();
	ObjectMap::const_iterator end();
	void accept(Visitor& v) override;
};

#endif //INC_3_SCENE_GROUP_H
