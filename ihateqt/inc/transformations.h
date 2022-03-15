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

errc transform_xyz_from_string(transform_xyz &self, const big_string &in);
errc transform_xyz_to_obj_string(const transform_xyz &self, big_string &out);

typedef struct transformations
{
	transform_xyz translate{};
	transform_xyz rotate{};
	transform_xyz scale{};
} transformations;

errc transforms_from_file(transformations &self, const big_string &path);
errc transforms_to_obj_string(const transformations &self, big_string &out);
errc transforms_to_file(const transformations &self, const big_string &path);
errc transforms_read_partial(transformations &self, const big_string &in);

errc get_string_for_transform_type(const transform_type type, small_string out);
errc get_transform_type_for_string(const small_string name, transform_type &out);

errc transformations_to_matrix(const transformations &self, mat4x4 &result);
errc transform_xyz_to_matrix(const transform_xyz &self, mat4x4 &result);

bool transform_xyz_is_valid(const transform_xyz &self);
bool transformations_valid(const transformations &self);

errc apply_transform(const vec4 *vertices, vec4 *transformed, const mat4x4 &matrix, int n_points);

#endif //IHATEQT_TRANSFORMATIONS_H
