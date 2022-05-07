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
	void exec() override;
};

#endif //INC_3_SCENE_COMMAND_H
