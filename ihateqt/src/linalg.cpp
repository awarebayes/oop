//
// Created by dev on 2/25/22.
//

#include "inc/linalg.h"
#include <cmath>
#include <sstream>

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
	mat4x4 result = mat4x4::identity();

	result = result * x_rot_matrix(x_rot);
	result = result * y_rot_matrix(y_rot);
	result = result * z_rot_matrix(z_rot);
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

vec4 operator+(vec4 const &lhs, vec4 const &rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
}

vec4 operator-(vec4 const &lhs, vec4 const &rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
}

double &vec4::operator[](int index)
{
	switch (index)
	{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
	}
}

double vec4::at(int index) const
{
	switch (index)
	{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			return 0;
	}
}

errc vec4::vertex_from_obj_string(const std::string &in, vec4 &result)
{
	std::stringstream ss(in);
	std::string is_vertex;
	errc ec = errc::ok;

	ss >> is_vertex >> result.x >> result.y >> result.z;
	result.w = 1;

	if (ss.fail() or is_vertex != "v")
		ec = errc::bad_from_string_read;
	return ec;
}

errc vec4_to_obj_string(const vec4 &self, std::string &result)
{
	std::stringstream ss;
	errc ec = errc::ok;
	ss << "v " << self.x << " " << self.y << " " << self.z << " ";
	if (not ss.fail())
		result = ss.str();
	else
		ec = errc::bad_to_string;
	return ec;
}

mat4x4 operator*(mat4x4 const &lhs, const mat4x4 &rhs)
{
	mat4x4 result = { 0 };
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			for (int inner = 0; inner < 4; inner++)
				result.mat[row][col] += lhs.mat[row][inner] * rhs.mat[inner][col];
	return result;
}

vec4 operator*(vec4 const &lhs, const mat4x4 &rhs)
{
	vec4 result = { 0, 0, 0, 0 };
	for (int col = 0; col < 4; col++)
		for (int inner = 0; inner < 4; inner++)
			result[col] += lhs.at(inner) * rhs.mat[inner][col];
	return result;
}

vec4 operator*(const mat4x4 &lhs, vec4 const &rhs)
{
	vec4 result = { 0, 0, 0, 0 };
	for (int col = 0; col < 4; col++)
		for (int inner = 0; inner < 4; inner++)
			result[col] += lhs.mat[col][inner] * rhs.at(inner);
	return result;
}

mat4x4 mat4x4::identity()
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
