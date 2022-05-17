//
// Created by dev on 5/1/22.
//
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include "math/inc/transformation.h"

Scale Scale::operator+(const Scale &scale) const
{
	return {x + scale.x, y + scale.y, z + scale.z};
}

Translation Translation::operator+(const Translation &other) const
{
	return {x + other.x, y + other.y, z + other.z};
}

Rotation Rotation::operator+(const Rotation &other) const
{
	return {x + other.x, y + other.y, z + other.z};
}

Transformation Transformation::operator+(const Scale &other) const
{
	return { rotation, translation, scale_ + other};
}

Transformation::Transformation(const Rotation &rotation_, const Translation &translation_, const Scale &scale__)
{
	rotation = rotation_;
	scale_ = scale__;
	translation = translation_;
}

Transformation Transformation::operator+(const Translation &other) const
{
	return { rotation, translation + other, scale_};
}

Transformation Transformation::operator+(const Rotation &other) const
{
	return {rotation + other, translation, scale_};
}

Transformation Transformation::operator+(const Transformation &other) const
{
	return {rotation + other.rotation, translation + other.translation, scale_ + other.scale_};
}

Transformation::Transformation(const Transformation &other)
{
	rotation = other.rotation;
	translation = other.translation;
	scale_ = other.scale_;
}

Matrix4 Transformation::get_matrix() const
{
	Vector3 trans = {translation.x, translation.y, translation.z};
	Vector3 scl = { scale_.x, scale_.y, scale_.z};
	Matrix4 id = Matrix4(1.0f);
	Matrix4 model = translate(id, trans);
	model = rotate(model, radians(rotation.x), Vector3(1.0f, 0.0f, 0.0f));
	model = rotate(model, radians(rotation.y), Vector3(0.0f, 1.0f, 0.0f));
	model = rotate(model, radians(rotation.z), Vector3(0.0f, 0.0f, -1.0f));
	model = scale(model, scl);
	return model;
}
