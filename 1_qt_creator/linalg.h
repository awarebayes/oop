//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_LINALG_H
#define INC_1_QT_CREATOR_LINALG_H

typedef struct Vec4
{
	double x, y, z, w;

	Vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w)
	{
	};

	double at(int index) const;

	double &operator[](int index);
} Vec4;

typedef struct Mat4x4
{
	double mat[4][4];
	static Mat4x4 eye();
} Mat4x4;

Mat4x4 x_rot_matrix(double deg);

Mat4x4 y_rot_matrix(double deg);

Mat4x4 z_rot_matrix(double deg);

Mat4x4 rotation_matrix(double x_rot, double y_rot, double z_rot);

Mat4x4 scale_matrix(double x_scale, double y_scale, double z_scale);

Mat4x4 translation_matrix(double x_translation, double y_translation, double z_translation);

Vec4 operator+(Vec4 const &lhs, Vec4 const &rhs);

Vec4 operator-(Vec4 const &lhs, Vec4 const &rhs);

Mat4x4 operator*(Mat4x4 const &lhs, const Mat4x4 &rhs);

Vec4 operator*(Vec4 const &lhs, const Mat4x4 &rhs);

Vec4 operator*(Mat4x4 const &lhs, const Vec4 &rhs);


#endif //INC_1_QT_CREATOR_LINALG_H
