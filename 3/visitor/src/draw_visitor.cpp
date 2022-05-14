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


void DrawVisitor::visit(Camera &cam)
{

}

void DrawVisitor::visit(Scene &scene)
{
	scene.accept(*this);
}

void DrawVisitor::visit(MeshModel &model)
{
	Matrix4 model_matrix = model.get_transform()->get_matrix();
	draw_model(model, model_matrix);
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

void DrawVisitor::visit_with_new_transform(VisibleGroup &group, const Matrix4 &transformation)
{
	for (auto &[_, object]: group)
		visit_with_new_transform(*object, transformation);
}

void DrawVisitor::visit(VisibleGroup &group)
{
	// Caution
	Matrix4 displacement = group.get_transform()->get_matrix();
	auto previous_transform = displacement;
	for (auto &[_, object]: group)
	{
		auto object_matrix = object->get_transform()->get_matrix();
		visit_with_new_transform(*object, previous_transform * object_matrix);
	}
}

void DrawVisitor::visit_with_new_transform(MeshModel &model, const Matrix4 &transformation)
{
	draw_model(model, transformation);
}

void DrawVisitor::visit_with_new_transform(VisibleObject &object, const Matrix4 &transform)
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

void DrawVisitor::draw_model(MeshModel &model, const Matrix4 &model_matrix)
{
	const auto& vertices = model.get_vertices();
	Matrix4 view_matrix = camera->get_view_matrix();
	Matrix4 projection_matrix = camera->get_projection_matrix();
	Matrix4 matr = projection_matrix * (view_matrix * model_matrix);
	for (const auto &line: model.get_lines())
	{
		Vertex v1 = matr * vertices[line.first];
		Vertex v2 = matr * vertices[line.second];
		canvas->draw_line(
				v1[0], v1[1],
				v2[0], v2[1]);
	}
}
