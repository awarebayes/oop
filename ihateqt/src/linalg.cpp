//
// Created by dev on 2/25/22.
//

#include "inc/linalg.h"
#include <cmath>
#include <sstream>
#include <cstring>

mat4x4 x_rot_matrix(double deg)
{
	double theta = deg * M_PI / 180;
	return {
			.mat = {
					{ 1, 0,          0,           0 },
					{ 0, cos(theta), -sin(theta), 0 },
					{ 0, sin(theta), cos(theta),  0 },
					{ 0, 0,          0,           1 }
			}
	};
}

mat4x4 y_rot_matrix(double deg)
{
	double theta = deg * M_PI / 180;
	return {
			.mat = {
					{ cos(theta),  0, sin(theta), 0 },
					{ 0,           1, 0,          0 },
					{ -sin(theta), 0, cos(theta), 0 },
					{ 0,           0, 0,          1 },
			}
	};
}

mat4x4 z_rot_matrix(double deg)
{
	double theta = deg * M_PI / 180;
	return {
			.mat = {
					{ cos(theta), -sin(theta), 0, 0 },
					{ sin(theta), cos(theta),  0, 0 },
					{ 0,          0,           1, 0 },
					{ 0,          0,           0, 1 }
			}
	};
}

mat4x4 rotation_matrix(double x_rot, double y_rot, double z_rot)
{
	mat4x4 result = mat_identity();

	result = mat_mul(result, x_rot_matrix(x_rot));
	result = mat_mul(result, y_rot_matrix(y_rot));
	result = mat_mul(result, z_rot_matrix(z_rot));
	return result;
}

mat4x4 scale_matrix(double sx, double sy, double sz)
{
	return {
			.mat = {
					{ sx, 0,  0,  0 },
					{ 0,  sy, 0,  0 },
					{ 0,  0,  sz, 0 },
					{ 0,  0,  0,  1 }
			}
	};
}


mat4x4 translation_matrix(double x_translation, double y_translation, double z_translation)
{
	return {
			.mat = {
					{ 1,             0,             0,             0 },
					{ 0,             1,             0,             0 },
					{ 0,             0,             1,             0 },
					{ x_translation, y_translation, z_translation, 1 }
			}
	};
}

errc vec4_from_obj_string(vec4 &result, const big_string &in)
{
	small_string line_type;
	errc ec = errc::ok;
	vec4 temp;

	if (sscanf(in.buf, "%s %lf %lf %lf", line_type,
	           &temp.components[0],
	           &temp.components[1],
	           &temp.components[2]) != 4)
		ec = errc::bad_from_string_read;
	temp.components[3] = 1;

	if (strcmp(line_type, "v") != 0)
		ec = errc::bad_from_string_read;

	if (ec == errc::ok)
		result = temp;
	return ec;
}

errc vec4_to_obj_string(big_string &result, const vec4 &self)
{
	sprintf(result.buf, "v %lf %lf %lf", self.components[0], self.components[1], self.components[2]);
	return errc::ok;
}

mat4x4 mat_mul(mat4x4 const &lhs, const mat4x4 &rhs)
{
	mat4x4 result = { 0 };
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			for (int inner = 0; inner < 4; inner++)
				result.mat[row][col] += lhs.mat[row][inner] * rhs.mat[inner][col];
	return result;
}

vec4 vec_mul(vec4 const &lhs, const mat4x4 &rhs)
{
	vec4 result = { 0, 0, 0, 0 };
	for (int col = 0; col < 4; col++)
		for (int inner = 0; inner < 4; inner++)
			result.components[col] += lhs.components[inner] * rhs.mat[inner][col];
	return result;
}

vec4 vec_add(vec4 const &lhs, const vec4 &rhs)
{
	vec4 result = { 0, 0, 0, 0 };
	for (int col = 0; col < 4; col++)
		result.components[col] = lhs.components[col] + rhs.components[col];
	return result;
}

vec4 vec_sub(vec4 const &lhs, const vec4 &rhs)
{
	vec4 result = { 0, 0, 0, 0 };
	for (int col = 0; col < 4; col++)
		result.components[col] = lhs.components[col] - rhs.components[col];
	return result;
}


mat4x4 mat_identity()
{
	return {
			{
					{ 1, 0, 0, 0 },
					{ 0, 1, 0, 0 },
					{ 0, 0, 1, 0 },
					{ 0, 0, 0, 1 },
			}
	};
}

errc apply_transform(vec4 *dest, const vec4 *source, const mat4x4 &matrix, int n_points)
{
	for (int i = 0; i < n_points; i++)
		dest[i] = vec_mul(source[i], matrix);
	return errc::ok;
}


vec4 vec_scale(vec4 const &vec, const double scale)
{
	vec4 scaled = vec;
	for (int i = 0; i < 3; i++)
		scaled.components[i] *= scale;
	return scaled;
}
