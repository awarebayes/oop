//
// Created by dev on 3/10/22.
//

#include <iostream>
#include "inc/domain.h"

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
			ec = read_obj3d(object, current_state.obj_path);
			if (ec == errc::ok)
				ec = appropriate_transformations(object, transforms);
			break;
		case command_type::save_object:
			// ec = save_transformed_obj3d(object, transforms, current_state.obj_path);
			break;
		case command_type::draw_object:
			ec = draw_object(current_state.scene, object, transforms);
			break;
		default:
			ec = errc::bad_command;
			break;
	}

	return ec;
}

static std::vector<vec4> apply_transform(const std::vector<vec4> &vertices, const mat4x4 &matrix)
{
	std::vector<vec4> transformed;
	transformed.reserve(vertices.size());

	for (const auto &vertex: vertices)
	{
		vec4 result = vertex * matrix;
		transformed.push_back(result);
	}

	return std::move(transformed);
}

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
		scene->addLine(point1.x, point1.y, point2.x, point2.y);
	}
	return ec;
}


