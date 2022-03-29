//
// Created by dev on 3/10/22.
//

#include "inc/transformations.h"
#include <cmath>
#include <cstring>
#include <inc/config.h>

bool transform_xyz_is_valid(const transform_xyz &self)
{
	if (std::isnan(self.x) || std::isnan(self.y) || std::isnan(self.z))
		return false;
	if (std::isinf(self.x) || std::isinf(self.y) || std::isinf(self.z))
		return false;
	if (self.type != transform_type::Translate && self.type != transform_type::Rotate &&
	    self.type != transform_type::Scale)
		return false;
	return true;
}

bool transformations_valid(const transformations &self)
{
	bool res = true;
	res &= transform_xyz_is_valid(self.translate);
	res &= transform_xyz_is_valid(self.rotate);
	res &= transform_xyz_is_valid(self.scale);
	return res;
}

errc transform_xyz_to_matrix(mat4x4 &result, const transform_xyz &self)
{
	if (not transform_xyz_is_valid(self))
		return errc::invalid_transformations;
	errc ec = errc::ok;
	switch (self.type)
	{
		case transform_type::Translate:
			result = translation_matrix(self.x, self.y, self.z);
			break;

		case transform_type::Rotate:
			result = rotation_matrix(self.x, self.y, self.z);
			break;

		case transform_type::Scale:
			result = scale_matrix(self.x, self.y, self.z);
			break;
		default:
			ec = errc::invalid_transformations;
			break;
	}
	return ec;
}

errc transformations_to_matrix(mat4x4 &result, const transformations &self)
{
	if (not transformations_valid(self))
		return errc::invalid_transformations;

	mat4x4 translation_mat = { .mat={ 0 }};
	mat4x4 rotation_mat = { .mat={ 0 }};
	mat4x4 scale_mat = { .mat={ 0 }};

	transform_xyz_to_matrix(translation_mat, self.translate);
	transform_xyz_to_matrix(rotation_mat, self.rotate);
	transform_xyz_to_matrix(scale_mat, self.scale);

	result = mat_identity();
	result = mat_mul(result, scale_mat);
	result = mat_mul(result, rotation_mat);
	result = mat_mul(result, translation_mat);
	return errc::ok;
}

void reset_transforms(transformations &self)
{
	self.rotate = { 0, 0, 180 };
	self.scale = { 1, 1, 1 };
	self.translate = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0 };
}
