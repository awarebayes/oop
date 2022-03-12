//
// Created by dev on 3/10/22.
//

#include <iostream>
#include "inc/domain.h"




errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms)
{
	if (object.vertices.empty() or object.lines.empty())
		return errc::bad_render_call;

	scene->clear();

	mat4x4 transform_mat;
	errc ec = errc::ok;
	ec = transformations_to_matrix(transforms, transform_mat);

	std::vector<vec4> transformed_vertices = apply_transform(object.vertices, transform_mat);

	for (const auto &line: object.lines)
	{
		vec4 point1 = transformed_vertices[line.first];
		vec4 point2 = transformed_vertices[line.second];
		scene->addLine(point1[0], point1[1], point2[0], point2[1]);
	}
	return ec;
}

errc load_object_and_transforms(obj3d &object, transformations &transforms, const std::string &path)
{
	errc ec = errc::ok;
	ec = obj3d::from_file(object, path);
	ec = transformations::from_file(transforms, path);
	if (ec == errc::transforms_not_found)
	{
		ec = appropriate_transformations(object, transforms);
		if (ec == errc::transforms_not_found)
			ec = errc::ok;
	}
	return ec;
}

errc save_object_and_transforms(const obj3d &object, const transformations &transforms, const std::string &path)
{
	obj3d::to_file(object, path);
	transformations::to_file(transforms, path);
}

errc entry_point(command_type command, state &current_state)
{
	obj3d &object = current_state.object;
	transformations &transforms = current_state.transforms;

	if (current_state.just_initialized)
	{
		object = obj3d::default_cube();
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
