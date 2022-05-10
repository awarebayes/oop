//
// Created by dev on 5/1/22.
//

#include <iostream>
#include "object/inc/camera.h"

void FPSCamera::accept(Visitor &v)
{
	v.visit(*this);
}

FPSCamera::FPSCamera(const Vector<3> &position, const Vector<3> &up, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Front = Vector<3>{0.0f, 0.0f, -1.0f};
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

FPSCamera::FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)  : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Front = Vector<3>{0.0f, 0.0f, -1.0f};
	Position = Vector<3>{posX, posY, posZ};
	WorldUp = Vector<3>{upX, upY, upZ};
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Matrix<4> FPSCamera::get_matrix() const
{
	return lookAt(Position, Position + Front, Up);
}

void FPSCamera::updateCameraVectors()
{
	Vector<3> front;
	front(0)= cosf(radians(Yaw)) * cosf(radians(Pitch));
	front(1) = sinf(radians(Pitch));
	front(2) = sinf(radians(Yaw)) * cosf(radians(Pitch));
	Front = front.normalize();
	Right = cross(Front, WorldUp).normalize();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = cross(Right, Front).normalize();
}

void FPSCamera::rotate(float x_offset, float y_offset)
{
	Yaw   += x_offset;
	Pitch += y_offset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
}

void FPSCamera::move(const Vector<3> &offset)
{
	Position = Position + offset;
	std::cout << "pox: " << Position(0) << " " << Position(1) << " " << Position(2) <<std::endl;
}

Matrix<4> Camera::get_matrix() const
{
	return Matrix<4>::identity();
}
