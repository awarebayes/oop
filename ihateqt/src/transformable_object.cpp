//
// Created by dev on 04/04/2022.
//
#include <inc/obj3d_util.h>
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
	obj3d temp_obj = {};
	errc ec = obj3d_from_file(temp_obj, path);

	if (ec == errc::ok)
	{
		free_obj3d(object.model);
		object.model = temp_obj;
		appropriate_transforms(object.transforms, object.model);
	}
	return ec;
}

errc trans_object_save(const transformable_object &object, const big_string &path)
{
	errc ec = errc::ok;
	obj3d save_copy{};
	obj3d model = object.model;
	transformations transforms = object.transforms;

	ec = obj3d_copy(save_copy, model);
	if (ec == errc::ok)
		ec = obj3d_apply_transform(save_copy, transforms);
	if (ec == errc::ok)
		ec = obj3d_to_file(save_copy, path);

	free_obj3d(save_copy);

	return ec;
}

errc trans_object_mutate_transform(transformable_object &object, transform_mutation mut)
{
	errc ec = errc::ok;
	mutate_transforms(object.transforms, mut);
	return ec;
}

transformable_object default_cube()
{
	transformable_object cube{};
	cube.model = obj3d_default_cube();
	appropriate_transforms(cube.transforms, cube.model);
	return cube;
}
