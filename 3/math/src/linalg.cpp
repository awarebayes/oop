//
// Created by dev on 5/8/22.
//

#include "math/inc/linalg.h"
#include "math/inc/linalg.hpp"

Vector<3> cross(const Vector<3> &v1, const Vector<3> &v2) {
	return {v1(1)*v2(2) - v1(2)*v2(1), v1(2)*v2(0) - v1(0)*v2(2), v1(0)*v2(1) - v1(1)*v2(0)};
}

float dot(const Vector<3> &v1, const Vector<3> &v2)
{
	return v1(0) * v2(0)  + v1(1) * v2(1) + v1(2) * v2(2);
}

Matrix<4> lookAt(const Vector<3> &eye, const Vector<3> & center, const Vector<3> & up)
{
	Vector<3> f = (center - eye);
	f = f.normalize();
	Vector<3>  u = (up).normalize();
	Vector<3>  s = (cross(f, u)).normalize();
	u = cross(s, f);

	Matrix<4> Result = Matrix<4>::identity();
	//Result(0, 0) = s(0);
	//Result(1, 0) = s(1);
	//Result(2, 0) = s(2);
	//Result(0, 1) = u(0);
	//Result(1, 1) = u(1);
	//Result(2, 1) = u(2);
	//Result(0, 2) =-f(0);
	//Result(1, 2) =-f(1);
	//Result(2, 2) =-f(2);
	//Result(3, 0) =-dot(s, eye);
	//Result(3, 1) =-dot(u, eye);
	//Result(3, 2) = dot(f, eye);

	Result(0, 0) = s(0);
	Result(0, 1) = s(1);
	Result(0, 2) = s(2);
	Result(1, 0) = u(0);
	Result(1, 1) = u(1);
	Result(1, 2) = u(2);
	Result(2, 0) =-f(0);
	Result(2, 1) =-f(1);
	Result(2, 2) =-f(2);
	Result(0, 3) =-dot(s, eye);
	Result(2, 3) =-dot(u, eye);
	Result(1, 3) = dot(f, eye);
	return Result;
}
