//
// Created by dev on 04/04/2022.
//
#include <inc/obj3d_util.h>
#include <inc/config.h>
#include "inc/transformable_object.h"

errc trans_object_draw(domain_scene scene, const transformable_object &object)
{
	obj3d draw_copy{};

	obj3d model = object.model;
	transformations transforms = object.transforms;

	errc ec = obj3d_copy(draw_copy, model);

	if (ec == errc::ok)
		ec = obj3d_apply_transform(draw_copy, transforms);
	if (ec == errc::ok)
		ec = obj3d_draw(scene, draw_copy);

	free_obj3d(draw_copy);

	return ec;
}

errc trans_object_load(transformable_object &object, const big_string &path)
{
	obj3d temp_model = {};
	errc ec = obj3d_from_file(temp_model, path);
	obj3d &model = object.model;

	if (ec == errc::ok)
	{
		free_obj3d(model);
		model = temp_model;
	}
	return ec;
}

errc trans_object_save(const transformable_object &object, const big_string &path)
{
	errc ec = errc::ok;
	obj3d save_copy{};
	obj3d model = object.model;
	transformations transforms = object.transforms;
	// transforms.translate = {0, 0, 0};

	ec = obj3d_copy(save_copy, model);
	if (ec == errc::ok)
		ec = obj3d_apply_transform(save_copy, transforms);
	if (ec == errc::ok)
		ec = obj3d_to_file(save_copy, path);

	free_obj3d(save_copy);

	return ec;
}

errc trans_object_mutate_transform(transformable_object &object, const transform_mutation mut)
{
	errc ec = mutate_transforms(object.transforms, mut);
	return ec;
}

errc trans_object_reset_transforms(transformable_object &object, int screen_width, int screen_height)
{
	reset_transforms(object.transforms, screen_width, screen_height);
	return errc::ok;
}

transformable_object default_cube()
{
	transformable_object cube{};

	cube.model = obj3d_default_cube();
	reset_transforms(cube.transforms, SCREEN_WIDTH, SCREEN_HEIGHT);

	return cube;
}
