//
// Created by dev on 5/1/22.
//

#ifndef INC_3_CAMERA_H
#define INC_3_CAMERA_H
#include "scene_object.h"

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
	virtual ~Camera() = default;

	virtual Matrix<4> get_matrix() const;
	void accept(Visitor& v) override {};
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class FPSCamera : public Camera
{
public:
	FPSCamera() = delete;
	explicit FPSCamera(const Vector<3>&position, const Vector<3>&up=Vector<3>{0, 1, 0}, float yaw=YAW, float pitch=PITCH);
	FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~FPSCamera() override = default;

	void accept(Visitor& v) override;
	[[nodiscard]] Matrix<4> get_matrix() const override;
	void rotate(float x_offset, float y_offset);
	void move(const Vector<3> &offset);
private:
	void updateCameraVectors();

	Vector<3> Position;
	Vector<3> Front;
	Vector<3> Up;
	Vector<3> Right;
	Vector<3> WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
};

#endif //INC_3_CAMERA_H
