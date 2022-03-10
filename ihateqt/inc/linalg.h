//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_LINALG_H
#define INC_1_QT_CREATOR_LINALG_H

#include <ostream>
#include "error.h"

typedef struct vec4
{
	double x, y, z, w;

	[[nodiscard]] double at(int index) const;

	static errc vertex_from_obj_string(const std::string &in);

	errc to_obj_string() const;

	double &operator[](int index);
} vec4;

typedef struct mat4x4
{
	double mat[4][4];
	static mat4x4 identity();
} mat4x4;

mat4x4 x_rot_matrix(double deg);

mat4x4 y_rot_matrix(double deg);

mat4x4 z_rot_matrix(double deg);

mat4x4 rotation_matrix(double x_rot, double y_rot, double z_rot);

mat4x4 scale_matrix(double x_scale, double y_scale, double z_scale);

mat4x4 translation_matrix(double x_translation, double y_translation, double z_translation);

vec4 operator+(vec4 const &lhs, vec4 const &rhs);

vec4 operator-(vec4 const &lhs, vec4 const &rhs);

mat4x4 operator*(mat4x4 const &lhs, const mat4x4 &rhs);

vec4 operator*(vec4 const &lhs, const mat4x4 &rhs);

vec4 operator*(mat4x4 const &lhs, const vec4 &rhs);


#endif //INC_1_QT_CREATOR_LINALG_H
