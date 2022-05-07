//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_SCENE_H
#define INC_3_TEST_SCENE_H

#include <vector>
#include <map>
#include "scene/inc/visible_group.h"

class Scene : Visitable
{
private:
	VisibleGroup visible_objects;
public:
	Scene() = default;
	virtual ~Scene() = default;

	int add_object(const std::shared_ptr<VisibleObject>& object);
	int clone_object(int object_id);
	bool remove_object(int object_id);
	std::shared_ptr<VisibleObject> get_object(int object_id);
	void accept(Visitor& v) override;
};

#endif //INC_3_TEST_SCENE_H
