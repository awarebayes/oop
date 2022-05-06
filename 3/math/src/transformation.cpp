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

std::shared_ptr<Transformation> Scale::share() const
{
	return std::make_shared<Scale>(x,y,z);
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

std::shared_ptr<Transformation> Translation::share() const
{
	return std::make_shared<Translation>(x,y,z);
}

Matrix<4> Rotation::get_matrix() const
{
	return x_rot_matrix(x) * y_rot_matrix(y) * z_rot_matrix(z);
}

std::shared_ptr<Transformation> Rotation::share() const
{
	return std::make_shared<Rotation>(x,y,z);
}

Matrix<4> Identity::get_matrix() const
{
	return mat;
}

std::shared_ptr<Transformation> Identity::share() const
{
	return std::make_shared<Identity>(get_matrix());
}


Matrix<4> CompositeTransformation::get_matrix() const
{
	return prev_transform->get_matrix() * this_transform->get_matrix();
}

std::shared_ptr<Transformation> CompositeTransformation::share() const
{
	return std::make_shared<Identity>(get_matrix());
}

CompositeTransformation::CompositeTransformation(const Transformation &transform)
{
	prev_transform = Identity(transform.get_matrix()).share();
	this_transform = Identity(Matrix<4>::identity()).share();
}

CompositeTransformation::CompositeTransformation(std::shared_ptr<Transformation> transform)
{
	prev_transform = std::move(transform);
	this_transform = Identity(Matrix<4>::identity()).share();
}

CompositeTransformation CompositeTransformation::compose(const Transformation &next_transform)
{
	this->this_transform = std::make_shared<CompositeTransformation>(next_transform);
	return {*this};
}

CompositeTransformation CompositeTransformation::compose(const std::shared_ptr<Transformation>& next_transform)
{
	this->this_transform = std::make_shared<CompositeTransformation>(next_transform);
	return {*this};
}
