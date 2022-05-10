//
// Created by dev on 5/7/22.
//

#ifndef INC_3_SCENE_COMMAND_H
#define INC_3_SCENE_COMMAND_H

#include "base_command.h"

class SceneCommand : public Command
{

};

class RenderSceneCommand : public SceneCommand
{
public:
	RenderSceneCommand() = default;
	~RenderSceneCommand() override = default;
	void exec() override;
};


class SetActiveCameraSceneCommand : public SceneCommand
{
public:

	explicit SetActiveCameraSceneCommand(int cam_id_) : cam_id(cam_id_) {};
	~SetActiveCameraSceneCommand() override = default;
	void exec() override;
private:
	int cam_id;
};

#endif //INC_3_SCENE_COMMAND_H
