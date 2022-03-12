//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_TRANSFORMATIONS_H
#define IHATEQT_TRANSFORMATIONS_H


#include "linalg.h"
#include "error.h"
#include <string>
#include <vector>

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

	static errc from_string(transform_xyz &self, const std::string &in);
	static errc to_obj_string(const transform_xyz &self, std::string &out);
} transform_xyz;

typedef struct transformations
{
	transform_xyz translate{};
	transform_xyz rotate{};
	transform_xyz scale{};

	static errc from_file(transformations &self, const std::string &path);
	static errc to_obj_string(const transformations &self, std::string &out);
	static errc to_file(const transformations &self, const std::string &path);
	static errc read_partial(transformations &self, const std::string &in);
} transformations;

errc get_string_for_transform_type(const transform_type type, std::string &out);
errc get_transform_type_for_string(const std::string &name, transform_type &out);

errc transformations_to_matrix(const transformations &self, mat4x4 &result);
errc transform_xyz_to_matrix(const transform_xyz &self, mat4x4 &result);

bool transform_xyz_is_valid(const transform_xyz &self);
bool transformations_valid(const transformations &self);

std::vector<vec4> apply_transform(const std::vector<vec4> &vertices, const mat4x4 &matrix);


#endif //IHATEQT_TRANSFORMATIONS_H
