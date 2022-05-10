//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TRANSFORMATION_H
#define INC_3_TRANSFORMATION_H

#include <memory>
#include <utility>
#include "linalg.hpp"

class BaseTransformation
{
public:
	[[nodiscard]] virtual Matrix<4> get_matrix() const = 0;
};

class Scale : public BaseTransformation
{
private:
	float x{1}, y{1}, z{1};
public:
	Scale() = default;
	Scale(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Scale() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	Scale operator +(const Scale &scale) const;
};

class Translation : public BaseTransformation
{
private:
	float x{}, y{}, z{};
public:
	Translation() = default;
	Translation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Translation() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	Translation operator +(const Translation &other) const;
};

class Rotation : public BaseTransformation
{
private:
	float x{}, y{}, z{};
public:
	Rotation() = default;
	Rotation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Rotation() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	Rotation operator +(const Rotation &other) const;
};

class Transformation : public BaseTransformation
{
private:
	Rotation rotation{};
	Translation translation{};
	Scale scale{};
public:
	Transformation() = default;
	Transformation(const Transformation &other);
	Transformation(const Rotation &rotation_, const Translation &translation_, const Scale &scale_);
	virtual ~Transformation() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	Transformation operator +(const Scale &scale) const;
	Transformation operator +(const Translation &other) const;
	Transformation operator +(const Rotation &other) const;
	Transformation operator +(const Transformation &other) const;
};


#endif //INC_3_TRANSFORMATION_H
