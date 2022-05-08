//
// Created by dev on 5/8/22.
//

#ifndef INC_3_LOGIC_H
#define INC_3_LOGIC_H

#include <command/facade.h>
#include "scene_meta.h"

class Logic
{
private:
	RendererFacade facade;
	SceneMeta meta;
public:
	void load_object(const std::string &path);
	void draw();
	void move_selected_object(int object_id, float dx, float dy, float dz);
	void rotate_selected_object(int object_id, float dx, float dy, float dz);
	void print_objects();
	bool has_object_id(int object_id);
};

#endif //INC_3_LOGIC_H
