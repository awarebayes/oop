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

Matrix4 Transformation::get_matrix()
{
	Vector3 trans = {translation.x, translation.y, translation.z};
	Vector3 scl = {scale.x, scale.y, scale.z};
	Matrix4 id = Matrix4(1.0f);
	Matrix4 model = glm::translate(id, trans);
	model = glm::rotate(model, glm::radians(rotation.x), Vector3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), Vector3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), Vector3(0.0f, 0.0f, -1.0f));
	model = glm::scale(model, scl);
	return model;

}
