//
// Created by dev on 2/25/22.
//

#include "inc/model.h"

#include <utility>

const Mesh3D &Model::get_current_object() const
{
	return current_object.get_value();
}

void Model::mutate_current_object(const Mesh3D &object)
{
	current_object.set_value(object);
}


const Transformations &Model::get_transformations() const
{
	return transform.get_value();
}

void Model::mutate_transformations(const Transformations &transformations)
{
	transform.set_value(transformations);
}


