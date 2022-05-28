//
// Created by dev on 5/7/22.
//

#ifndef INC_3_OBJECT_COMMAND_H
#define INC_3_OBJECT_COMMAND_H

#include "base_command.h"
#include "math/inc/linalg.h"
#include "math/inc/glm_wrapper.h"

class ObjectCommand : public Command {};

class ObjectMoveCommand : public ObjectCommand
{
public:
	ObjectMoveCommand(int object_id, const Vector3 &offset);
	void exec() override;
private:
	Vector3 offset;
	int object_id;
};


class ObjectScaleCommand : public ObjectCommand
{
public:
	ObjectScaleCommand(int object_id, const Vector3 &scale);
	void exec() override;
private:
	Vector3 scale;
	int object_id;
};

class ObjectRotateCommand : public ObjectCommand
{
public:
	ObjectRotateCommand(int object_id, const Vector3 &rotation);
	void exec() override;
private:
	Vector3 rotation;
	int object_id;
};

class ObjectDeleteCommand : public ObjectCommand
{
public:
	explicit ObjectDeleteCommand(int object_id);
	void exec() override;
	[[nodiscard]] bool get_result() const;
private:
	int object_id;
	bool succ;
};

#endif //INC_3_OBJECT_COMMAND_H
