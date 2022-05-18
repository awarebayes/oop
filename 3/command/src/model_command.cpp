//
// Created by dev on 5/7/22.
//

#include <command/inc/model_command.h>
#include <manager/inc/load_manager.h>
#include <manager/inc/manager_solution.h>

void LoadMeshCommand::exec()
{
	auto load_manager = ManagerSolution::get_load_manager();
	result = load_manager->load_mesh_model(_path);
}

LoadMeshCommand::LoadMeshCommand(const std::string &path)
{
	_path = path;
}

int LoadMeshCommand::get_result() const
{
	return result;
}
