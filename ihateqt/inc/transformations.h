//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_TRANSFORMATIONS_H
#define IHATEQT_TRANSFORMATIONS_H


#include "linalg.h"
#include "error.h"
#include "mishalib.h"

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

typedef struct transform_mutation
{
	transform_type type;
	axis ax;
	double value;
} transform_mutation;

transformations transformation_translate(double x, double y, double z);

transformations transformation_scale(double x, double y, double z);

transformations transformation_rotate(double x, double y, double z);

errc transformations_to_matrix(mat4x4 &result, const transformations &self);

errc transform_xyz_to_matrix(mat4x4 &result, const transform_xyz &self);

void reset_transforms(transformations &self);

transformations compose_transforms(const transformations &self, const transformations &other);

bool transform_xyz_is_valid(const transform_xyz &self);

bool transformations_valid(const transformations &self);

void mutate_transforms(transformations &self, transform_mutation mut);

transformations identity_transforms();

#endif //IHATEQT_TRANSFORMATIONS_H
