//
// Created by dev on 5/2/22.
//

#ifndef INC_3_MESH_MODEL_LOADER_H
#define INC_3_MESH_MODEL_LOADER_H
#include "load/inc/loader.h"
#include <memory>

class MeshModelLoader : public ModelLoader
{
public:
	std::shared_ptr<Model> load_model(const std::string &path) override;
};

#endif //INC_3_MESH_MODEL_LOADER_H
