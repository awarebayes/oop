//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_MATH_H
#define INC_3_TEST_MATH_H
#include "gtest/gtest.h"
#include "math/inc/linalg.hpp"
#include "math/inc/transformation.h"

void matrix_eq(const Matrix<3> &m1, const Matrix<3> &m2)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			EXPECT_FLOAT_EQ(m1(i, j), m2(i, j));
}

void matrix_eq(const Matrix<4> &m1, const Matrix<4> &m2)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_FLOAT_EQ(m1(i, j), m2(i, j));
}

TEST(Math, VectorCreation)
{
	Vector<3> xyz{};
	xyz(0) = 1;
	xyz(1) = 2;
	xyz(2) = 3;
	EXPECT_EQ(xyz(0), 1);
	EXPECT_EQ(xyz(1), 2);
	EXPECT_EQ(xyz(2), 3);
}

TEST(Math, VectorCreationAlt)
{
	Vector<3> xyz{1, 2, 3};
	EXPECT_EQ(xyz(0), 1);
	EXPECT_EQ(xyz(1), 2);
	EXPECT_EQ(xyz(2), 3);
}


TEST(Math, MatrixMultiplication)
{
	Matrix<3> m1
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
	};

	Matrix<3> m2
	{
		1, 2, 3,
		1, 2, 3,
		1, 2, 3,
	};
	matrix_eq(m1 * m2,Matrix<3>{
		6, 12, 18,
		15, 30, 45,
		24, 48, 72
	});

	matrix_eq(m2 * m1,Matrix<3>{
			30, 36, 42,
			30, 36, 42,
			30, 36, 42
	});
}



TEST(Math, TransformationTranslate)
{
	auto t1 = Translation(0, 10, 0);
	auto t2 = Translation(0, -10, 0);
	auto c = CompositeTransformation(t1).compose(t2);
	Matrix<4> m = c.get_matrix();

	matrix_eq(m ,Matrix<4>{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
	});

}


#endif //INC_3_TEST_MATH_H
