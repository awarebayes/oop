//
// Created by dev on 3/6/22.
//
#include "../inc/transformations.h"
#include "../inc/linalg.h"


void TransformXYZ::mutate(Axis axis, double value)
{
	switch (axis)
	{
		case Axis::X:
			x = value;
			break;
		case Axis::Y:
			y = value;
			break;
		case Axis::Z:
			z = value;
			break;
	}
}

Mat4x4 Transformations::getMatrix() const
{
	Mat4x4 result = Mat4x4::eye();
	Mat4x4 scale_mat = scale_matrix(scale.x, scale.y, scale.z);
	Mat4x4 rotate_mat = rotation_matrix(rotate.x, rotate.y, rotate.z);
	Mat4x4 translation_mat = translation_matrix(translate.x, translate.y, translate.z);

	result = result * scale_mat;
	result = result * rotate_mat;
	result = result * translation_mat;
	return result;
}

void Transformations::mutate(TransformType type, Axis axis, double value)
{
	switch (type)
	{
		case TransformType::Translate:
			translate.mutate(axis, value);
			break;
		case TransformType::Rotate:
			rotate.mutate(axis, value);
			break;
		case TransformType::Scale:
			scale.mutate(axis, value);
			break;
	}
}


