//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CAMERA_H
#define INC_3_CAMERA_H
#include "scene_object.h"

enum class CameraType
{
	FPS,
	Test
};

class ICamera : public InvisibleObject
{
public:
	ICamera() = default;
	~ICamera() override = default;

	[[nodiscard]] virtual Matrix4 get_view_matrix() const = 0;
	[[nodiscard]] virtual Matrix4 get_projection_matrix()  const = 0;
	void accept(Visitor& v) = 0;
	virtual void rotate(float x_offset, float y_offset) = 0;
	virtual void move(const Vector3 &offset) = 0;
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class FPSCamera : public ICamera
{
private:
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
	void updateCameraVectors();
public:
	FPSCamera() = delete;
	explicit FPSCamera(const Vector3 &position, const Vector3&up=Vector3{0, 1, 0}, float yaw=YAW, float pitch=PITCH);
	FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~FPSCamera() override = default;

	void accept(Visitor& v) override;
	[[nodiscard]] Matrix4 get_view_matrix() const override;
	[[nodiscard]] Matrix4 get_projection_matrix() const override; // transformation move to
	void rotate(float x_offset, float y_offset) override;
	void move(const Vector3 &offset) override;
};

class TestCamera : public ICamera
{
public:
	TestCamera() = default;
	[[nodiscard]] Matrix4 get_view_matrix() const override;
	[[nodiscard]] Matrix4 get_projection_matrix() const override;
	void accept(Visitor& v) override;
	void rotate(float x_offset, float y_offset) override {};
	void move(const Vector3 &offset) override {};
};

class CameraFactory
{
public:
	CameraFactory() = delete;
	~CameraFactory() = delete;
	CameraFactory(CameraFactory&) = delete;
	static std::shared_ptr<ICamera> create(const CameraType &cam_type);
};

#endif //INC_3_CAMERA_H
