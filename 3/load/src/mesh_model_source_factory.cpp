//
// Created by dev on 22/05/2022.
//

#include <load/inc/mesh_model_source_factory.h>
#include <load/inc/mesh_objfile_source.h>


std::unique_ptr <MeshModelSource> SourceFactory::create(SourceType type, const std::string &path)
{
	if (type == SourceType::ObjFile)
	{
		return std::make_unique<ObjFileMeshSource>(path);
	}
}

