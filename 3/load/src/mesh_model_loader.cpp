//
// Created by dev on 5/2/22.
//
#include "load/inc/mesh_model_loader.h"
#include "load/inc/mesh_model_builder.h"

std::shared_ptr<Model> MeshModelLoader::load_model(const std::string &path)
{
	return MeshModelDirector(path).build_model();
}
