//
// Created by dev on 5/2/22.
//

#ifndef INC_3_LOADER_H
#define INC_3_LOADER_H
#include <memory>
#include "object/inc/drawable_model.h"


class ModelLoader
{
public:
	virtual std::shared_ptr<Model> load_model(const std::string &path) = 0;
};


class AllLoader
{
private:
	std::unique_ptr<ModelLoader> model_loader{};
public:
	virtual std::shared_ptr<Model> load_model(const std::string &path);
};

#endif //INC_3_LOADER_H
