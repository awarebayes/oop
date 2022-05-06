//
// Created by dev on 5/3/22.
//

#include <visitor/inc/draw_visitor.h>

#include <utility>


void DrawVisitor::visit(VisibleGroup &group)
{

}

void DrawVisitor::visit(Camera &cam)
{

}

void DrawVisitor::visit(Scene &scene)
{
}

void DrawVisitor::visit(MeshModel &model)
{
	Matrix<4> model_matrix = model._transform->get_matrix();
	Matrix<4> camera_matrix = camera->get_matrix();
	Matrix<4> transformation_matrix = camera_matrix * model_matrix;
	const auto vertices = model.get_vertices();
	for (const auto &line: model.get_lines())
	{
		Vertex v1 = transformation_matrix * vertices[line.first];
		Vertex v2 = transformation_matrix * vertices[line.second];
		canvas->draw_line(
				v1(0), v1(1),
				v2(0), v2(1));
	}
}

DrawVisitor::DrawVisitor(std::shared_ptr<Canvas> canvas_, std::shared_ptr<Camera> camera_)
{
	canvas = std::move(canvas_);
	camera = std::move(camera_);
}

void DrawVisitor::visit(VisibleObject &object)
{
	if (object.is_mesh())
	{
		visit(dynamic_cast<MeshModel&>(object));
	}
}

