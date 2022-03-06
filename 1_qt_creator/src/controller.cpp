//
// Created by dev on 3/6/22.
//

#include <inc/controller.h>
#include <QFileDialog>


Controller::Controller(Model &model, MainWindow &view) : model_(model), view_(view) {}

void Controller::mutate_transformations(TransformType type, Axis axis, double value)
{
	Transformations current_transform = model_.get_transformations();
	current_transform.mutate(type, axis, value);
	model_.mutate_transformations(current_transform);
}

const Mesh3D &Controller::get_current_object() const
{
	return model_.get_current_object();
}

Mat4x4 Controller::get_transformation_matrix() const
{
	return model_.get_transformation_matrix();
}

void Controller::apply_appropriate_transformations()
{
	const Mesh3D &object = get_current_object();
	Transformations new_transform = object.get_appropriate_transformations();
	model_.mutate_transformations(new_transform);
}

void Controller::load_object()
{
	QString filename = QFileDialog::getOpenFileName(nullptr, "Open .obj file", "./", "Obj file (*.obj)");
	Mesh3D new_object = Mesh3D::from_file(filename.toStdString());
	if (not new_object.is_empty())
	{
		model_.mutate_current_object(new_object);
		apply_appropriate_transformations();
	}
};
