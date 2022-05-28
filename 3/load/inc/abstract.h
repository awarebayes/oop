//
// Created by dev on 5/2/22.
//

#ifndef INC_3_ABSTRACT_H
#define INC_3_ABSTRACT_H
#include <memory>
#include "object/inc/drawable_model.h"

class ModelBuilder
{
public:
	virtual void read_vertices() = 0;
	virtual void read_lines() = 0;
};

class ModelDirector
{
public:
	virtual void build_model() = 0;
};

#endif //INC_3_ABSTRACT_H
