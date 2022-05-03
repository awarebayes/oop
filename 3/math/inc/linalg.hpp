//
// Created by dev on 5/1/22.
//

#ifndef INC_3_LINALG_HPP
#define INC_3_LINALG_HPP

#include "math/inc/linalg.h"
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
Vector<n> Vector<n>::operator*(Matrix<n> &other)
{
	return Vector<n>();
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

#endif //INC_3_LINALG_HPP
