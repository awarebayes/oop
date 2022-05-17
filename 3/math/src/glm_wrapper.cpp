//
// Created by dev on 5/17/22.
//

#include <math/inc/glm_wrapper.h>

Matrix4 translate(const Matrix4&mat, const Vector3& offset)
{
	return glm::translate(mat, offset);
}

Matrix4 rotate(const Matrix4&mat, float rad, const Vector3& offset)
{
	return glm::rotate(mat, rad, offset);
}

Matrix4 scale(const Matrix4&mat, const Vector3& scale)
{
	return glm::scale(mat, scale);
}

Matrix4 lookAt(const Vector3& pos, const Vector3& eye, const Vector3& dir)
{
	return glm::lookAt(pos, eye, dir);
}

Vector3 normalize(const Vector3& vec)
{
	return glm::normalize(vec);
}

Matrix4 perspective(float rad, float aspect, float zNear, float zFar)
{
	return glm::perspective(rad, aspect, zNear, zFar);
}
