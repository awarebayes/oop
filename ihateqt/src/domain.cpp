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

	mat4x4 transform_mat;
	errc ec = errc::ok;
	ec = transformations_to_matrix(transforms, transform_mat);

	vec4 *transformed = (vec4 *)malloc(object.n_vertices * sizeof(vec4));
	if (transformed == nullptr)
		ec = errc::bad_malloc;

	if (ec == errc::ok)
		ec = apply_transform(object.vertices, transformed, transform_mat, object.n_vertices);

	for (int i = 0; i < object.n_lines and ec == errc::ok; i++)
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

errc load_object_and_transforms(obj3d &object, transformations &transforms, const big_string &path)
{

	obj3d temp_object;
	transformations temp_transforms;

	errc ec = errc::ok;
	bool object_loaded = false;
	ec = obj3d_from_file(temp_object, path);
	if (ec == errc::ok)
	{
		object_loaded = true;
		ec = transforms_from_file(temp_transforms, path);
	}
	if (object_loaded and ec == errc::transforms_not_found)
	{
		ec = appropriate_transformations(temp_object, temp_transforms);
		if (ec == errc::transforms_not_found)
			ec = errc::ok;
	}

	if (ec == errc::ok)
	{
		free_obj3d(object);
		object = temp_object;
		transforms = temp_transforms;
	}
	return ec;
}

errc save_object_and_transforms(const obj3d &object, const transformations &transforms, const big_string &path)
{
	errc ec = errc::ok;
	ec = obj3d_to_file(object, path);
	if (ec == errc::ok)
		ec = transforms_to_file(transforms, path);
	return ec;
}

errc entry_point(command_type command, state &current_state)
{
	obj3d &object = current_state.object;
	transformations &transforms = current_state.transforms;

	if (current_state.just_initialized)
	{
		object = obj3d_default_cube();
		appropriate_transformations(object, transforms);
		current_state.just_initialized = false;
	}

	errc ec = errc::ok;

	switch (command)
	{
		case command_type::load_object:
			ec = load_object_and_transforms(object, transforms, current_state.obj_path);
			break;
		case command_type::save_object:
			ec = save_object_and_transforms(object, transforms, current_state.obj_path);
			break;
		case command_type::draw_object:
			ec = draw_object(current_state.scene, object, transforms);
			break;
		case command_type::default_view:
			appropriate_transformations(object, transforms);
			break;
		default:
			ec = errc::bad_command;
			break;
	}

	return ec;
}
