//
// Created by dev on 5/3/22.
//

#ifndef INC_3_VISIBLE_GROUP_H
#define INC_3_VISIBLE_GROUP_H
#include "object/inc/scene_object.h"
#include <map>

class VisibleGroup : public VisibleObject
{
	using object_map = std::map<int, std::shared_ptr<VisibleObject>>;
	object_map objects{};
	int obj_count = 0;
public:
	VisibleGroup() = default;
	~VisibleGroup() override = default;

	bool is_grouped() override {return true;};
	int add_object(const std::shared_ptr<VisibleObject>& obj);
	bool remove_object(int object_id);
	std::shared_ptr<VisibleObject> get_object(int object_id);
	object_map::const_iterator begin();
	object_map::const_iterator end();
	void accept(Visitor& v) override;
};

#endif //INC_3_VISIBLE_GROUP_H
