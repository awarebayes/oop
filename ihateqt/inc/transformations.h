//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_TRANSFORMATIONS_H
#define IHATEQT_TRANSFORMATIONS_H


#include "linalg.h"
#include "error.h"
#include <string>

enum struct axis
{
	X, Y, Z
};

enum struct transform_type
{
	Translate, Scale, Rotate
};

typedef struct transform_xyz
{
	double x;
	double y;
	double z;
	transform_type type;
} transform_xyz;

typedef struct transformations
{
	transform_xyz translate{};
	transform_xyz rotate{};
	transform_xyz scale{};
} transformations;

errc transformations_to_matrix(const transformations &self, mat4x4 &result);
errc transform_xyz_to_matrix(const transform_xyz &self, mat4x4 &result);
bool transform_xyz_is_valid(const transform_xyz &self);
bool transformations_valid(const transformations &self);

#endif //IHATEQT_TRANSFORMATIONS_H
