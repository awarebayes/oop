//
// Created by dev on 5/2/22.
//

#ifndef INC_3_MESH_COMPONENT_FACTORY_H
#define INC_3_MESH_COMPONENT_FACTORY_H
#include "factory/inc/component_factory.h"
#include "load/inc/loader.h"

class MeshComponentFactory : public ComponentFactory
{
	std::unique_ptr<ModelLoader> build_loader() { return  };
};

#endif //INC_3_MESH_COMPONENT_FACTORY_H
