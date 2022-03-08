//
// Created by dev on 2/26/22.
//

#include "inc/renderer.h"

Renderer::Renderer(int width, int height, QObject &parent)
{
	scene = std::make_shared<QGraphicsScene>(new QGraphicsScene(0, 0, width, height, &parent));
	scene->addRect(scene->sceneRect());
}

static std::vector<Vec4> apply_transform(const std::vector<Vec4> &vertices, const Mat4x4 &matrix)
{
	std::vector<Vec4> transformed;

	std::transform(vertices.begin(), vertices.end(), std::back_inserter(transformed),
				   [&matrix](Vec4 vertex)
				   { return vertex * matrix; });

	return transformed;
}

auto Renderer::draw_object(Mesh3D const &mesh, Transformations const &transformations) const -> cpp::result<void, errc>
{
	if (not mesh.can_draw())
		return cpp::fail(errc::bad_render_call);

	scene->clear();
	std::vector<Vec4> transformed_vertices = apply_transform(mesh.vertices, transformations.getMatrix());

	for (const auto &triangle : mesh.indexes)
	{
		int index1 = triangle.index[0];
		int index2 = triangle.index[1];
		int index3 = triangle.index[2];

		Vec4 point1 = transformed_vertices[index1];
		Vec4 point2 = transformed_vertices[index2];
		Vec4 point3 = transformed_vertices[index3];

		scene->addLine(point1.x, point1.y, point2.x, point2.y);
		scene->addLine(point2.x, point2.y, point3.x, point3.y);
		scene->addLine(point1.x, point1.y, point3.x, point3.y);
	}
	return {};
}

Renderer::~Renderer() = default;