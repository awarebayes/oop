//
// Created by dev on 5/1/22.
//

#ifndef INC_3_LINALG_H
#define INC_3_LINALG_H

#include <cstddef>
#include <cassert>
#include <initializer_list>


template <size_t n>
class Matrix
{
private:
	float components[n * n]{};
public:
	float& operator()(size_t i, size_t j);
	float operator()(size_t i, size_t j) const;
	Matrix(std::initializer_list<float> init);
	static Matrix<n> identity();
};


template <size_t n>
class Vector
{
private:
	float components[n];
public:
	Vector();
	Vector(std::initializer_list<float> init);
	float& operator()(size_t i);
	float operator()(size_t i) const;
};

template <size_t n>
Vector<n> operator*(const Vector<n> &lhs, const Matrix<n>& rhs);

template <size_t n>
Vector<n> operator*(const Matrix<n> &lhs, const Vector<n> &rhs);

#endif //INC_3_LINALG_H
