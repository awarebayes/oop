//
// Created by dev on 2/25/22.
//

#include "inc/model.h"

#include <utility>

Mat4x4 Model::get_transformation_matrix() const
{
	return transform.get_value().getMatrix();
}

Model::Model()
{
	current_object.set_value(Mesh3D::default_cube());
}

const Mesh3D &Model::get_current_object() const
{
	return current_object.get_value();
}

void Model::mutate_current_object(Mesh3D object)
{
	current_object.set_value(std::move(object));
}

void Model::connect_view(MainWindow &view)
{
	transform.connect(view.transform_changed);
	current_object.connect(view.object_changed);
}

Transformations Model::get_transformations()
{
	return transform.get_value();
}

void Model::mutate_transformations(Transformations transformations)
{
	transform.set_value(transformations);
}


