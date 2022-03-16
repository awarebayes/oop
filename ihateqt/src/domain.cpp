//
// Created by dev on 3/10/22.
//

#include <iostream>
#include "inc/domain.h"

errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms)
{
	if (object.n_vertices == 0 or object.n_lines == 0)
		return errc::bad_render_call;

	scene->clear();

	errc ec = errc::ok;

	vec4 *transformed = (vec4 *)malloc(object.n_vertices * sizeof(vec4));
	if (transformed == nullptr)
		ec = errc::bad_malloc;

	ec = copy_transformed_vertices(transformed, transforms, object);

	for (int i = 0; ec == errc::ok and i < object.n_lines; i++)
	{
		line l = object.lines[i];
		vec4 point1 = transformed[l.first];
		vec4 point2 = transformed[l.second];
		scene->addLine(point1.components[0], point1.components[1],
					   point2.components[0], point2.components[1]);
	}

	free(transformed);

	return ec;
}

errc load_object(obj3d &object, const big_string &path)
{
	obj3d temp_object{};

	errc ec = errc::ok;
	ec = obj3d_from_file(temp_object, path);

	if (ec == errc::ok)
	{
		free_obj3d(object); // ПРЕДЫДУЩИЙ ОСВОБОЖДАЕМ, НОВЫЙ ЗАГРУЖАЕМ
		object = temp_object; // тут происходит move
	}

	// не надо освобождать temp_transforms

	return ec;
}

errc save_object(const obj3d &object, const big_string &path)
{
	errc ec = errc::ok;
	ec = obj3d_to_file(object, path);
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
			// ec = save_object(object, transforms, com.obj_path);
			break;
		case command_type::draw_object:
			// todo: создать объект с трансформациями
			ec = draw_object(com.scene, object, transforms);
			break;
		case command_type::default_view:
			reset_transforms(transforms);
			break;
		default:
			ec = errc::bad_command;
			break;
	}

	return ec;
}
