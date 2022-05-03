//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TRANSFORMATION_H
#define INC_3_TRANSFORMATION_H

#include <memory>
#include <utility>
#include "linalg.hpp"

class Transformation
{
public:
	virtual Matrix<4> get_matrix() const = 0;
	virtual std::shared_ptr<Transformation> share() const = 0;
};

class Scale : public Transformation
{
private:
	float x, y, z;
public:
	Scale(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Scale() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	[[nodiscard]] std::shared_ptr<Transformation> share() const override;
};

class Translation : public Transformation
{
private:
	float x, y, z;
public:
	Translation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Translation() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	[[nodiscard]] virtual std::shared_ptr<Transformation> share() const;
};

class Rotation : public Transformation
{
private:
	float x, y, z;
public:
	Rotation(float x, float y, float z) : x(x), y(y), z(z) {};
	virtual ~Rotation() = default;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	[[nodiscard]] std::shared_ptr<Transformation> share() const override;
};


class Identity : public Transformation
{
	Matrix<4> mat;
public:
	explicit Identity() : mat(Matrix<4>::identity()){};
	explicit Identity(const Matrix<4>& trans) : mat(trans) {};
	explicit Identity(const Transformation& trans) : mat(trans.get_matrix()) {};
	[[nodiscard]] Matrix<4> get_matrix() const override;
};

class CompositeTransformation : public Transformation
{
private:
	std::shared_ptr<Transformation> this_transform{};
	std::shared_ptr<Transformation> prev_transform{};
public:
	explicit CompositeTransformation(std::shared_ptr<Transformation> transform) : prev_transform(std::move(transform)) {};
	explicit CompositeTransformation(const Transformation &transform);
	CompositeTransformation compose(const std::shared_ptr<Transformation>& next_transform);
	[[nodiscard]] Matrix<4> get_matrix() const override;
};


#endif //INC_3_TRANSFORMATION_H
