//
// Created by dev on 5/7/22.
//

#ifndef INC_3_MODEL_COMMAND_H
#define INC_3_MODEL_COMMAND_H

#include "base_command.h"
#include <string>

class ModelCommand : public Command
{

};

class LoadMeshCommand : public ModelCommand
{
public:
	LoadMeshCommand() = delete;
	explicit LoadMeshCommand(const std::string& path);
	~LoadMeshCommand() override = default;
	void exec() override;
	[[nodiscard]] int get_result() const;
private:
	std::string _path;
	int result;
};

#endif //INC_3_MODEL_COMMAND_H
