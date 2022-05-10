//
// Created by dev on 5/8/22.
//

#ifndef INC_3_CAMERA_COMMAND_H
#define INC_3_CAMERA_COMMAND_H

#include "base_command.h"
#include "object/inc/camera.h"

class CameraCommand : public Command {};

class CameraNewCommand : public CameraCommand
{
public:
	CameraNewCommand();
	void exec() override;
	[[nodiscard]] int get_result() const;
private:
	int camera_id = -1;
};

class CameraMoveCommand : public CameraCommand
{
public:
	CameraMoveCommand(int camera_id, const Vector<3> &offset);
	void exec() override;
private:
	Vector<3> offset;
	int camera_id;
};



class CameraRotateCommand : public CameraCommand
{
public:
	CameraRotateCommand(int camera_id, float x_offset, float y_offset);
	void exec() override;
private:
	float x_offset, y_offset;
	int camera_id;
};

#endif //INC_3_CAMERA_COMMAND_H
