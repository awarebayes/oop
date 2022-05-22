//
// Created by dev on 5/3/22.
//

#include <visitor/inc/draw_visitor.h>
#include <utility>

DrawVisitor::DrawVisitor(std::shared_ptr<Canvas> canvas_, std::shared_ptr<ICamera> camera_)
{
	canvas = std::move(canvas_);
	camera = std::move(camera_);
}


void DrawVisitor::visit(ICamera &cam)
{

}

void DrawVisitor::visit(Scene &scene)
{
	scene.accept(*this);
}

void DrawVisitor::visit(SceneGroup &group)
{
	Matrix4 displacement = group.get_transform_matrix();
	add_transform_context(displacement);
	for (auto &[_, object]: group)
	{
		object->accept(*this);
	}
	add_transform_context(inverse(displacement));
}

void DrawVisitor::clear_transform_context()
{
	context = Matrix4(1.0f);
}

void DrawVisitor::add_transform_context(const Matrix4 &ctx)
{
	context = context * ctx;
}

void DrawVisitor::visit(MeshModelReference &ref)
{
	const auto model = ref.base;
	const auto model_matrix = ref.get_transform_matrix();
	const auto& vertices = model->get_vertices();
	Matrix4 view_matrix = camera->get_view_matrix();
	Matrix4 projection_matrix = camera->get_projection_matrix();
	Matrix4 matr = projection_matrix * (view_matrix * (context * model_matrix));
	for (const auto &line: model->get_lines())
	{
		Vertex v1 = matr * vertices[line.first];
		Vertex v2 = matr * vertices[line.second];
		canvas->draw_line(
				v1[0], v1[1],
				v2[0], v2[1]);
	}
}

void DrawVisitor::visit(LightSource &lightSource)
{

}
