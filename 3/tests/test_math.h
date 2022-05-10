//
// Created by dev on 5/1/22.
//

#ifndef INC_3_TEST_MATH_H
#define INC_3_TEST_MATH_H
#include "gtest/gtest.h"
#include "math/inc/linalg.hpp"
#include "math/inc/transformation.h"

void matrix_eq(const glm::mat3x3 &m1, const glm::mat3 &m2)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			EXPECT_FLOAT_EQ(m1[i][j], m2[i][j]);
}

void matrix_eq(const glm::mat4 &m1, const glm::mat4 &m2)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			EXPECT_FLOAT_EQ(m1[i][j], m1[i][j]);
}


#endif //INC_3_TEST_MATH_H
