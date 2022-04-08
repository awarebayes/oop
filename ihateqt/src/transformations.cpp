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

void reset_transforms(transformations &self, int screen_width, int screen_height)
{
	self.rotate = { 0, 0, 180, transform_type::Rotate };
	self.scale = { 1, 1, 1 , transform_type::Scale};
	self.translate = { static_cast<double>(screen_width / 2), static_cast<double>(screen_height / 2), 0, transform_type::Translate };
}

void mutate_xyz(transform_xyz &xyz, double val, axis ax)
{
	switch (ax)
	{
		case axis::X:
			xyz.x = val;
			break;
		case axis::Y:
			xyz.y = val;
			break;
		case axis::Z:
			xyz.z = val;
			break;
	}
}


errc mutate_transforms(transformations &self, transform_mutation mut)
{
	errc ec = errc::ok;
	switch (mut.type)
	{
		case transform_type::Translate:
			mutate_xyz(self.translate, mut.value, mut.ax);
			break;
		case transform_type::Scale:
			mutate_xyz(self.scale, mut.value, mut.ax);
			break;
		case transform_type::Rotate:
			mutate_xyz(self.rotate, mut.value, mut.ax);
			break;
		default:
			ec = errc::invalid_argument;
	}
	return ec;
}
