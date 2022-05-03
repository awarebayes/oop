//
// Created by dev on 5/2/22.
//

#ifndef INC_3_COMPONENT_FACTORY_H
#define INC_3_COMPONENT_FACTORY_H
#include "load/inc/loader.h"



class ComponentFactory
{
public:
	std::unique_ptr<ModelLoader> build_loader() = 0;
};

#endif //INC_3_COMPONENT_FACTORY_H
