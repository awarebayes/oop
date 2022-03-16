//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_LINALG_H
#define INC_1_QT_CREATOR_LINALG_H

#include <ostream>
#include "error.h"
#include "mishalib.h"

typedef struct vec4
{
	double components[4];
} vec4;


typedef struct mat4x4
{
	double mat[4][4];
} mat4x4;

mat4x4 mat_identity();

mat4x4 x_rot_matrix(double deg);

mat4x4 y_rot_matrix(double deg);

mat4x4 z_rot_matrix(double deg);

mat4x4 rotation_matrix(double x_rot, double y_rot, double z_rot);

mat4x4 scale_matrix(double x_scale, double y_scale, double z_scale);

mat4x4 translation_matrix(double x_translation, double y_translation, double z_translation);

errc vec4_from_obj_string(vec4 &result, const big_string &in);

errc vec4_to_obj_string(big_string &result, const vec4 &self);

mat4x4 mul_mat(mat4x4 const &lhs, const mat4x4 &rhs);

vec4 vec_sub(vec4 const &lhs, const vec4 &rhs);

vec4 mul_vec(vec4 const &lhs, const mat4x4 &rhs);

vec4 scale_vec(vec4 const &vec, const double scale);

errc apply_transform(const vec4 *vertices, vec4 *transformed, const mat4x4 &matrix, int n_points);

#endif //INC_1_QT_CREATOR_LINALG_H
