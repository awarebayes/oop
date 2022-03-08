//
// Created by dev on 3/6/22.
//

#include <inc/controller.h>
#include <QFileDialog>
#include <QMessageBox>
#include <inc/obj_io.h>


Controller::Controller(Model &model) : model_(model)
{
}

void Controller::mutate_transformations(TransformType type, Axis axis, double value) const
{
	Transformations current_transform = model_.get_transformations();
	current_transform.mutate(type, axis, value);
	model_.mutate_transformations(current_transform);
}

const Mesh3D &Controller::get_current_object() const
{
	return model_.get_current_object();
}

const Transformations &Controller::get_transformations() const
{
	return model_.get_transformations();
}

void Controller::set_appropriate_transformations()
{
	const Mesh3D &object = get_current_object();
	Transformations new_transform = get_appropriate_transformations(object);
	model_.mutate_transformations(new_transform);
}

void Controller::load_object()
{
	QString filename = QFileDialog::getOpenFileName(nullptr, "Open .obj file", "./", "Obj file (*.obj)");
	if (filename.isEmpty())
		return;

	auto maybe_read_result = read_obj_file(filename.toStdString());
	if (maybe_read_result.has_value())
	{
		ReadResult result = maybe_read_result.value();
		model_.mutate_current_object(result.mesh);
		model_.mutate_transformations(result.transformations);
	}
	else
		show_error_dialog(maybe_read_result.error());
}

void Controller::load_default_cube()
{
	model_.mutate_current_object(Mesh3D::default_cube());
	set_appropriate_transformations();
}

void Controller::show_error_dialog(errc code)
{
	const std::string &message = error_map.at(code);
	QMessageBox::critical(nullptr, "Critical", QString::fromStdString(message));
}

void Controller::save_object()
{
	QString filename = QFileDialog::getSaveFileName(nullptr, "Save .obj file", "./", "Obj file (*.obj)");

	if (filename.isEmpty())
		return;

	auto object = model_.get_current_object();
	auto transform = model_.get_transformations();
	auto maybe_error = write_obj_file(filename.toStdString(), object, transform);

	if (maybe_error.has_error())
		show_error_dialog(maybe_error.error());
}

