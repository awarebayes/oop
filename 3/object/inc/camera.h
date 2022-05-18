//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CAMERA_H
#define INC_3_CAMERA_H
#include "scene_object.h"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera : public InvisibleObject
{
public:
	Camera() = default;
	~Camera() override = default;

	[[nodiscard]] virtual glm::mat4 get_view_matrix() const;
	[[nodiscard]] virtual glm::mat4 get_projection_matrix() const;
	void accept(Visitor& v) override {};
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class FPSCamera : public Camera
{
public:
	FPSCamera() = delete;
	explicit FPSCamera(const glm::vec3&position, const glm::vec3&up=glm::vec3{0, 1, 0}, float yaw=YAW, float pitch=PITCH);
	FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~FPSCamera() override = default;

	void accept(Visitor& v) override;
	[[nodiscard]] glm::mat4 get_view_matrix() const override;
	[[nodiscard]] glm::mat4 get_projection_matrix() const override;
	void rotate(float x_offset, float y_offset);
	void move(const glm::vec3 &offset);
private:
	void updateCameraVectors();

	glm::vec3 Position{};
	glm::vec3 Front{};
	glm::vec3 Up{};
	glm::vec3 Right{};
	glm::vec3 WorldUp{};
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float aspect = 1.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
	float fov = 90.0f;
};

#endif //INC_3_CAMERA_H
