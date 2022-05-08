//
// Created by dev on 5/1/22.
//

#include "object/inc/camera.h"

std::unique_ptr<Transformation> Camera::look_at_object(VisibleObject &object) const
{
	return nullptr;
}

void Camera::change_position(float x, float y, float z)
{
	position = Vector<3>{x, y, z};
}

void Camera::change_look_direction(float x, float y, float z)
{
	look_direction = Vector<3>{x, y, z};
}

Matrix<4> Camera::get_matrix() const
{
	return Matrix<4>::identity();
}

void Camera::accept(Visitor &v)
{
	v.visit(*this);
}

Matrix<4> Camera::viewport()
{
	return {};
}

