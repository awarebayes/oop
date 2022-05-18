//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TRANSFORMATION_H
#define INC_3_TRANSFORMATION_H

#include <memory>
#include <utility>
#include "linalg.hpp"
#include "glm_wrapper.h"

class BaseTransformation
{
};

class Scale : public BaseTransformation
{
public:
	float x{1}, y{1}, z{1};
	Scale() = default;
	Scale(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Scale() = default;
	Scale operator +(const Scale &scale) const;
};

class Translation : public BaseTransformation
{
public:
	float x{}, y{}, z{};
	Translation() = default;
	Translation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Translation() = default;
	Translation operator +(const Translation &other) const;
};

class Rotation : public BaseTransformation
{
public:
	float x{}, y{}, z{};
	Rotation() = default;
	Rotation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Rotation() = default;
	Rotation operator +(const Rotation &other) const;
};

class Transformation : public BaseTransformation
{
private:
	Rotation rotation{};
	Translation translation{};
	Scale scale_{};
public:
	Transformation() = default;
	Transformation(const Transformation &other);
	Transformation(const Rotation &rotation_, const Translation &translation_, const Scale &scale_);
	virtual ~Transformation() = default;
	[[nodiscard]] Matrix4 get_matrix() const;
	Transformation operator +(const Scale &scale) const;
	Transformation operator +(const Translation &other) const;
	Transformation operator +(const Rotation &other) const;
	Transformation operator +(const Transformation &other) const;
};


#endif //INC_3_TRANSFORMATION_H
