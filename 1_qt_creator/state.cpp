//
// Created by dev on 2/25/22.
//

#include "state.h"

Mat4x4 State::get_transformation_matrix()
{
	Mat4x4 result = Mat4x4::eye();

	Mat4x4 scale_mat = scale_matrix(transform.scale.x, transform.scale.y, transform.scale.z);
	Mat4x4 rotate_mat = rotation_matrix(transform.rotate.x, transform.rotate.y, transform.rotate.z);
	Mat4x4 translation_mat = translation_matrix(transform.translate.x, transform.translate.y, transform.translate.z);

	result = result * scale_mat;
	result = result * rotate_mat;
	result = result * translation_mat;
	return result;
}

State::State()
{
	current_object = Mesh3D::default_cube();
}
