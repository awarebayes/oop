//
// Created by dev on 22/05/2022.
//

#ifndef INC_3_MESH_MODEL_SOURCE_FACTORY_H
#define INC_3_MESH_MODEL_SOURCE_FACTORY_H

#include <load/inc/mesh_model_source.h>
#include <memory>

class SourceFactory
{
public:
	static std::unique_ptr<MeshModelSource> create(SourceType type, const std::string &path);
};

#endif //INC_3_MESH_MODEL_SOURCE_FACTORY_H
