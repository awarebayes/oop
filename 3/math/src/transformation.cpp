//
// Created by dev on 5/1/22.
//
#include <cmath>
#include "math/inc/transformation.h"


Matrix<4> x_rot_matrix(float deg)
{
	float theta = deg * M_PI / 180;
	return
	{
		1, 0,           0,            0,
		0, cosf(theta), -sinf(theta), 0,
		0, sinf(theta), cosf(theta),  0,
		0, 0,           0,            1
	};
}

Matrix<4> y_rot_matrix(float deg)
{
	float theta = deg * M_PI / 180;
	return {
		cosf(theta),  0, sinf(theta), 0,
		0,            1, 0,           0,
		-sinf(theta), 0, cosf(theta), 0,
		0,            0, 0,           1,
	};
}

Matrix<4> z_rot_matrix(float deg)
{
	float theta = deg * M_PI / 180;
	return {
			cosf(theta), -sinf(theta), 0, 0,
			sinf(theta), cosf(theta), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
	};
}

Matrix<4> Scale::get_matrix() const
{
	return {
		x, 0,  0,  0,
		0,  y, 0,  0,
		0,  0,  z, 0,
		0,  0,  0,  1,
	};
}


Scale Scale::operator+(const Scale &scale) const
{
	return {x + scale.x, y + scale.y, z + scale.z};
}

Matrix<4> Translation::get_matrix() const
{
	return {
		1,             0,             0,             x,
		0,             1,             0,             y,
		0,             0,             1,             z,
		0,             0,             0,             1
	};
}


Translation Translation::operator+(const Translation &other) const
{
	return {x + other.x, y + other.y, z + other.z};
}

Matrix<4> Rotation::get_matrix() const
{
	return x_rot_matrix(x) * y_rot_matrix(y) * z_rot_matrix(z);
}

Rotation Rotation::operator+(const Rotation &other) const
{
	return {x + other.x, y + other.y, z + other.z};
}

Matrix<4> Transformation::get_matrix() const
{
	return translation.get_matrix() * rotation.get_matrix() * scale.get_matrix();
}

Transformation Transformation::operator+(const Scale &other) const
{
	return {rotation, translation, scale + other};
}

Transformation::Transformation(const Rotation &rotation_, const Translation &translation_, const Scale &scale_)
{
	rotation = rotation_;
	scale = scale_;
	translation = translation_;
}

Transformation Transformation::operator+(const Translation &other) const
{
	return {rotation, translation + other, scale};
}

Transformation Transformation::operator+(const Rotation &other) const
{
	return {rotation + other, translation, scale};
}

Transformation Transformation::operator+(const Transformation &other) const
{
	return {rotation + other.rotation, translation + other.translation, scale + other.scale};
}

Transformation::Transformation(const Transformation &other)
{
	rotation = other.rotation;
	translation = other.translation;
	scale = other.scale;
}
