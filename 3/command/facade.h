//
// Created by dev on 5/7/22.
//

#ifndef INC_3_FACADE_H
#define INC_3_FACADE_H

#include <command/inc/base_command.h>
#include <command/inc/model_command.h>
#include <command/inc/object_command.h>
#include <command/inc/scene_command.h>
#include <command/inc/camera_command.h>
#include <memory>

class RendererFacade
{
public:
	void exec(const std::shared_ptr<Command> &command) {command->exec();};
};

#endif //INC_3_FACADE_H
