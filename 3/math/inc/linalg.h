//
// Created by dev on 5/1/22.
//

#ifndef INC_3_LINALG_H
#define INC_3_LINALG_H

#include <cstddef>
#include <cassert>
#include <initializer_list>
#include <array>


template <size_t n>
class Matrix
{
private:
	float components[n * n]{};
public:
	Matrix(std::initializer_list<float> init);

	static Matrix<n> identity();

	float& operator()(size_t i, size_t j);
	float operator()(size_t i, size_t j) const;
};


template <size_t n>
class Vector
{
private:
	float components[n];
public:
	Vector();
	Vector(std::initializer_list<float> init);
	explicit Vector(std::array<float, n> init);
	float& operator()(size_t i);
	float operator()(size_t i) const;
	[[nodiscard]] float length() const;
	Vector<n> normalize() const;
};

template <size_t n>
Vector<n> operator*(const Vector<n> &lhs, const Matrix<n>& rhs);

template <size_t n>
Vector<n> operator*(const Matrix<n> &lhs, const Vector<n> &rhs);

Vector<3> cross(const Vector<3> &v1, const Vector<3> &v2);

float dot(const Vector<3> &v1, const Vector<3> &v2);

Matrix<4> lookAt(const Vector<3> &eye, const Vector<3> & center, const Vector<3> & up);

#endif //INC_3_LINALG_H
