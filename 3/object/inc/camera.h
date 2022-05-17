//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CAMERA_H
#define INC_3_CAMERA_H
#include "scene_object.h"

class Camera : public InvisibleObject
{
public:
	Camera() = default;
	~Camera() override = default;

	[[nodiscard]] virtual Matrix4 get_view_matrix() const;
	[[nodiscard]] virtual Matrix4 get_projection_matrix() const;
	void accept(Visitor& v) override {};
	virtual void rotate(float x_offset, float y_offset) {};
	virtual void move(const Vector3 &offset) {};
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class FPSCamera : public Camera
{
public:
	FPSCamera() = delete;
	explicit FPSCamera(const Vector3 &position, const Vector3&up=Vector3{0, 1, 0}, float yaw=YAW, float pitch=PITCH);
	FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~FPSCamera() override = default;

	void accept(Visitor& v) override;
	[[nodiscard]] Matrix4 get_view_matrix() const override;
	[[nodiscard]] Matrix4 get_projection_matrix() const override;
	void rotate(float x_offset, float y_offset) override;
	void move(const Vector3 &offset) override;
private:
	void updateCameraVectors();

	Vector3 Position{};
	Vector3 Front{};
	Vector3 Up{};
	Vector3 Right{};
	Vector3 WorldUp{};
	float Yaw;
	float Pitch;
	float aspect = 1.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
};

#endif //INC_3_CAMERA_H
