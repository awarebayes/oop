//
// Created by dev on 5/3/22.
//

#include <visitor/inc/draw_visitor.h>

#include <utility>

DrawVisitor::DrawVisitor(std::shared_ptr<Canvas> canvas_, std::shared_ptr<Camera> camera_)
{
	canvas = std::move(canvas_);
	camera = std::move(camera_);
}

void DrawVisitor::visit(VisibleGroup &group)
{
	Matrix<4> displacement = group.get_transform()->get_matrix();
	for (auto &[_, object]: group)
	{
		auto object_matrix = object->get_transform()->get_matrix();
		visit_with_new_transform(*object, displacement * object_matrix);
	}
}

void DrawVisitor::visit(Camera &cam)
{

}

void DrawVisitor::visit(Scene &scene)
{

}

void DrawVisitor::visit(MeshModel &model)
{
	Matrix<4> model_matrix = model.get_transform()->get_matrix();
	Matrix<4> camera_matrix = camera->get_matrix();
	Matrix<4> transformation_matrix = camera_matrix * model_matrix;
	draw_model(model, transformation_matrix);
}

void DrawVisitor::visit(VisibleObject &object)
{
	object.accept(*this);
}

void DrawVisitor::visit(MeshModelReference &ref)
{
	auto matrix = ref.get_transform()->get_matrix();
	visit_with_new_transform(*ref.deref(), matrix);
}

void DrawVisitor::visit_with_new_transform(VisibleGroup &group, const Matrix<4> &transformation)
{
	for (auto &[_, object]: group)
		visit_with_new_transform(*object, transformation);
}


void DrawVisitor::visit_with_new_transform(MeshModel &model, const Matrix<4> &transformation)
{
	Matrix<4> camera_matrix = camera->get_matrix();
	Matrix<4> transformation_matrix = camera_matrix * transformation;
	draw_model(model, transformation_matrix);
}

void DrawVisitor::visit_with_new_transform(VisibleObject &object, const Matrix<4> &transform)
{
	if (object.is_mesh())
	{
		auto model = dynamic_cast<MeshModel&>(object);
		visit_with_new_transform(model, transform);
	}
	if (object.is_grouped())
	{
		auto group = dynamic_cast<VisibleGroup&>(object);
		visit_with_new_transform(group, transform);
	}
	if (object.is_reference())
	{
		auto reference = dynamic_cast<MeshModelReference&>(object);
		visit_with_new_transform(*reference.deref(), transform);
	}
}

void DrawVisitor::draw_model(MeshModel &model, const Matrix<4> &transformation_matrix)
{
	const auto& vertices = model.get_vertices();
	for (const auto &line: model.get_lines())
	{
		Vertex v1 = transformation_matrix * vertices[line.first];
		Vertex v2 = transformation_matrix * vertices[line.second];
		canvas->draw_line(
				v1(0), v1(1),
				v2(0), v2(1));
	}
}
