//
// Created by dev on 5/1/22.
//

#ifndef INC_3_LINALG_HPP
#define INC_3_LINALG_HPP

#include "math/inc/linalg.h"
#include <cmath>

template<size_t n>
float& Matrix<n>::operator()(size_t i, size_t j)
{
	assert(i * n + j < n * n);
	return components[i * n + j];
}

template<size_t n>
float Matrix<n>::operator()(size_t i, size_t j) const
{
	assert(i * n + j < n * n);
	return components[i * n + j];
}

template<size_t n>
Matrix<n> operator*(const Matrix<n> &self, const Matrix<n> &other)
{
	Matrix<n> res{};
	for (size_t row = 0; row < n; row++)
		for (size_t col = 0; col < n; col++)
			for (size_t inner = 0; inner < n; inner++)
				res(row, col) += self(row, inner) * other(inner, col);
	return res;
}

template<size_t n>
Matrix<n>::Matrix(std::initializer_list<float> init)
{
	assert(init.size() == 0 or init.size() == n*n);
	int i = 0;
	for (auto el: init)
		components[i++] = el;
}

template<size_t n>
Matrix<n> Matrix<n>::identity()
{
	Matrix<n> matrix{};
	for (int i = 0; i < n; i++)
		matrix(i, i) = 1;
	return matrix;
}

template<size_t n>
Vector<n> operator*(const Vector<n> &lhs, const Matrix<n> &rhs)
{
	Vector<n> result;
	for (int col = 0; col < n; col++)
		for (int inner = 0; inner < n; inner++)
			result(col) += lhs(inner) * rhs(inner, col);
	return result;
}

template<size_t n>
Vector<n> operator*(const Matrix<n> &lhs, const Vector<n> &rhs)
{
	Vector<n> result;
	for (int col = 0; col < n; col++)
		for (int inner = 0; inner < n; inner++)
			result(col) += lhs(col, inner) * rhs(inner);
	return result;
}

template<size_t n>
float &Vector<n>::operator()(size_t i)
{
	assert(i < n);
	return components[i];
}

template<size_t n>
Vector<n>::Vector(std::initializer_list<float> init)
{
	assert(init.size() == 0 or init.size() == n);
	int i = 0;
	for (auto el: init)
		components[i++] = el;
}

template<size_t n>
Vector<n>::Vector()
{
	for (int i = 0; i < n; i++)
		components[i] = 0;
}

template<size_t n>
float Vector<n>::operator()(size_t i) const
{

	assert(i < n);
	return components[i];
}

template<size_t n>
float Vector<n>::length() const
{
	float sum;
	for (int i =0; i < n; i++)
		sum += components[i];
	return sqrtf(sum);
}

template<size_t n>
Vector<n> Vector<n>::normalize() const
{
	std::array<float, n> args_arr;
	float len = length();
	for (int i=0; i < n; i++)
		args_arr[i] = components[i] / len;
	return Vector<n>(args_arr);
}

//Vector<3> cross(const Vector<3> &v1, const Vector<3> &v2) {
//	return {v1(1)*v2(2) - v1(2)*v2(1), v1(2)*v2(0) - v1(0)*v2(2), v1(0)*v2(1) - v1(1)*v2(0)};
//}

#endif //INC_3_LINALG_HPP
