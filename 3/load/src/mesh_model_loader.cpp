//
// Created by dev on 5/2/22.
//
#include <load/inc/mesh_model_source_factory.h>
#include "load/inc/mesh_model_loader.h"
#include "load/inc/mesh_model_builder.h"

std::shared_ptr<Model> MeshModelLoader::load_model(const std::string &path)
{
	auto source = SourceFactory::create(SourceType::ObjFile, path);
	auto director = MeshModelDirector();
	auto builder = std::make_shared<MeshModelBuilder>(std::move(source));
	director.set_builder(builder);
	director.build_model();
	return builder->get_result();
}
