//
// Created by dev on 5/1/22.
//

#include <iostream>
#include <manager/inc/transform_manager.h>
#include "object/inc/camera.h"
#include "math/inc/glm_wrapper.h"


void FPSCamera::accept(Visitor &v)
{
	v.visit(*this);
}

FPSCamera::FPSCamera(const Vector3 &position, const Vector3 &up, float yaw, float pitch)
{
	Transformer(*this).translate(position.x, position.y, position.z);
	Front = Vector3{0.0f, 0.0f, -1.0f};
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

FPSCamera::FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	Front = Vector3{0.0f, 0.0f, -1.0f};
	Transformer(*this).translate(posX, posY, posZ);
	Front = Vector3{0.0f, 0.0f, -1.0f};
	WorldUp = Vector3{upX, upY, upZ};
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Matrix4 FPSCamera::get_view_matrix() const
{
	auto Position = transform->get_pos();
	return glm::lookAt(Position, Position + Front, Up);
}

void FPSCamera::updateCameraVectors()
{
	Vector3 front;
	front.x = cos(radians(Yaw)) * cos(radians(Pitch));
	front.y = sin(radians(Pitch));
	front.z = sin(radians(Yaw)) * cos(radians(Pitch));
	Front = normalize(front);
	Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = normalize(cross(Right, Front));
}

void FPSCamera::rotate(float x_offset, float y_offset)
{
	Yaw   += x_offset;
	Pitch += y_offset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	updateCameraVectors();
}

Matrix4 FPSCamera::get_projection_matrix() const
{
	return perspective(radians(90.0f), aspect, zNear, zFar);
}

Matrix4 TestCamera::get_view_matrix() const
{
	return Matrix4(1.0f);
}

Matrix4 TestCamera::get_projection_matrix() const
{
	return Matrix4(1.0f);
}

void TestCamera::accept(Visitor &v)
{
	v.visit(*this);
}

std::shared_ptr<ICamera> CameraFactory::create(const CameraType &cam_type)
{
	if (cam_type == CameraType::Test)
		return std::make_shared<TestCamera>();
	if (cam_type == CameraType::FPS)
		return std::make_shared<FPSCamera>(Vector3(0, 0, -100));
}
