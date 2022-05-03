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
	virtual std::unique_ptr<DrawableModel> collect() = 0;
};

class ModelDirector
{
public:
	virtual std::unique_ptr<DrawableModel> build_model() = 0;
};

#endif //INC_3_ABSTRACT_H
