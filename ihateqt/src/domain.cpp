//
// Created by dev on 3/10/22.
//

#include <inc/obj3d_util.h>
#include "inc/domain.h"


errc entry_point(command &com)
{
	static transformable_object object = default_cube();
	errc ec = errc::ok;

	switch (com.type)
	{
		case command_type::load_object:
			ec = trans_object_load(object, com.obj_path);
			break;
		case command_type::save_object:
			ec = trans_object_save(object, com.obj_path);
			break;
		case command_type::draw_object:
			ec = trans_object_draw(com.scene, object);
			break;
		case command_type::mutate_transforms:
			ec = trans_object_mutate_transform(object, com.mutation);
			break;
		default:
			ec = errc::bad_command;
			break;
	}

	return ec;
}
