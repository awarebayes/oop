//
// Created by dev on 3/10/22.
//

#include "inc/transformations.h"
#include <cmath>


bool transform_xyz_is_valid(const transform_xyz &self)
{
	if (std::isnan(self.x) || std::isnan(self.y) || std::isnan(self.z))
		return false;
	if (std::isinf(self.x) || std::isinf(self.y) || std::isinf(self.z))
		return false;
	if (self.type == transform_type::Translate || self.type == transform_type::Rotate || self.type == transform_type::Scale)
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

errc transform_xyz_to_matrix(const transform_xyz &self, mat4x4 &result)
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
	}
	return ec;
}

errc transformations_to_matrix(const transformations &self, mat4x4 &result)
{
	if (not transformations_valid(self))
		return errc::invalid_transformations;

	mat4x4 translation_mat = {.mat={0}};
	mat4x4 rotation_mat = {.mat={0}};
	mat4x4 scale_mat = {.mat={0}};

	transform_xyz_to_matrix(self.translate, translation_mat);
	transform_xyz_to_matrix(self.rotate, rotation_mat);
	transform_xyz_to_matrix(self.scale, scale_mat);

	result = mat4x4::identity();
	result = result * scale_mat;
	result = result * rotation_mat;
	result = result * translation_mat;
}