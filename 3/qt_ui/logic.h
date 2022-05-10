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
	int load_object(const std::string &path);
	void draw();
	void move_object(int object_id, float dx, float dy, float dz);
	void rotate_object(int object_id, float dx, float dy, float dz);
	std::string print_objects();
	bool has_object_id(int object_id);
	bool has_camera_id(int camera_id);
	int new_camera();
	void set_active_camera(int camera_id);
	void move_camera(int camera_id, float dx, float dy, float dz);
	void rotate_camera(int camera_id, float x_offset, float y_offset);
};

#endif //INC_3_LOGIC_H
