//
// Created by dev on 5/7/22.
//

#ifndef INC_3_LOAD_MANAGER_H
#define INC_3_LOAD_MANAGER_H

#include <string>
#include <memory>
#include "base_manager.h"

class LoadManager : public BaseManager
{
public:
	LoadManager() = default;
	~LoadManager() override = default;
	LoadManager(const LoadManager &) = delete;
	int load_mesh_model(const std::string &path);
};

class LoadManagerCreator
{
public:
	std::shared_ptr<LoadManager> get();
private:
	void create();
	std::shared_ptr<LoadManager> singleton;
};

#endif //INC_3_LOAD_MANAGER_H
