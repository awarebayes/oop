//
// Created by dev on 5/1/22.
//

#include <iostream>
#include "object/inc/camera.h"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void FPSCamera::accept(Visitor &v)
{
	v.visit(*this);
}

FPSCamera::FPSCamera(const glm::vec3 &position, const glm::vec3 &up, float yaw, float pitch)
{
	Front = glm::vec3{0.0f, 0.0f, -1.0f};
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

FPSCamera::FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	Front = glm::vec3{0.0f, 0.0f, -1.0f};
	Position = glm::vec3{posX, posY, posZ};
	WorldUp = glm::vec3{upX, upY, upZ};
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 FPSCamera::get_view_matrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

void FPSCamera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = glm::normalize(glm::cross(Right, Front));
}

void FPSCamera::rotate(float x_offset, float y_offset)
{
	Yaw   += x_offset;
	Pitch += y_offset;
	std::cout << "Yaw " << Yaw << " Pitch " << Pitch << "\n";
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	updateCameraVectors();
}

void FPSCamera::move(const glm::vec3 &offset)
{
	Position = Position + offset;
}

glm::mat4 FPSCamera::get_projection_matrix() const
{
	return glm::perspective(glm::radians(90.0f), aspect, zNear, zFar);
}

glm::mat4 Camera::get_view_matrix() const
{
	return glm::mat4(1.0f);
}

glm::mat4 Camera::get_projection_matrix() const
{
	return glm::mat4(1.0f);
}
