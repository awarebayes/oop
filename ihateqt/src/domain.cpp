//
// Created by dev on 3/10/22.
//

#include "inc/domain.h"

errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms)
{
	obj3d transformed_object{};
	errc ec = obj3d_apply_transform_then_copy(transformed_object, object, transforms);

	if (ec == errc::ok)
		ec = obj3d_draw(scene, transformed_object);

	free_obj3d(transformed_object);

	return ec;
}

errc load_object(obj3d &object, const big_string &path)
{
	errc ec = obj3d_from_file(object, path);
	return ec;
}

errc save_transformed_object(const obj3d &object, const transformations &transforms, const big_string &path)
{
	errc ec = errc::ok;
	obj3d transformed_object{};

	ec = obj3d_apply_transform_then_copy(transformed_object, object, transforms);
	if (ec == errc::ok)
		ec = obj3d_to_file(transformed_object, path);

	free_obj3d(transformed_object);

	return ec;
}

errc entry_point(command &com)
{
	static obj3d object = obj3d_default_cube();
	transformations transforms = com.transforms;
	errc ec = errc::ok;

	switch (com.type)
	{
		case command_type::load_object:
			ec = load_object(object, com.obj_path);
			break;
		case command_type::save_object:
			ec = save_transformed_object(object, transforms, com.obj_path);
			break;
		case command_type::draw_object:
			ec = draw_object(com.scene, object, transforms);
			break;
		default:
			ec = errc::bad_command;
			break;
	}

	return ec;
}
