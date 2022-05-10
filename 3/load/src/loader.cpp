//
// Created by dev on 5/2/22.
//

#include <load/inc/loader.h>
#include "load/inc/mesh_model_builder.h"



std::shared_ptr<DrawableModel> AllLoader::load_model(const std::string &path)
{
	return model_loader->load_model(path);
}
