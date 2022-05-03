//
// Created by dev on 5/2/22.
//

#ifndef INC_3_LOADER_H
#define INC_3_LOADER_H
#include "object/inc/drawable_model.h"
#include <memory>


class ModelLoader
{
public:
	virtual std::unique_ptr<DrawableModel> load_model(const std::string &path) = 0;
};


class AllLoader
{
private:
	std::unique_ptr<ModelLoader> model_loader{};
public:
	virtual std::unique_ptr<DrawableModel> load_model(const std::string &path);
};

#endif //INC_3_LOADER_H
