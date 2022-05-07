//
// Created by dev on 5/7/22.
//

#include <command/inc/model_command.h>
#include <manager/inc/load_manager.h>

void LoadMeshCommand::exec()
{
	auto load_manager = LoadManagerCreator().get();
	result = load_manager->load_mesh_model(_path);
}

LoadMeshCommand::LoadMeshCommand(const std::string &path, int &result_) : result(result_)
{
	_path = path;
}

int LoadMeshCommand::get_result() const
{
	return result;
}
