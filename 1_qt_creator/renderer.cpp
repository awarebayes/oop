//
// Created by dev on 2/26/22.
//

#include "renderer.h"

Renderer::Renderer(int width, int height, QObject &parent) : width(width), height(height)
{
	scene = new QGraphicsScene(0,0, width, height, &parent);
	scene->addRect(scene->sceneRect());
}

void Renderer::draw_object(const Mesh3D &mesh, const Mat4x4 &transformations) const
{
	scene->clear();
	for (const auto &triangle: mesh.indexes)
	{
		int index1 = triangle.index[0];
		int index2 = triangle.index[1];
		int index3 = triangle.index[2];

		Vec4 point1 = mesh.vertices[index1];
		Vec4 point2 = mesh.vertices[index2];
		Vec4 point3 = mesh.vertices[index3];

		point1 = point1 * transformations;
		point2 = point2 * transformations;
		point3 = point3 * transformations;

		scene->addLine(point1.x, point1.y, point2.x, point2.y);
		scene->addLine(point2.x, point2.y, point3.x, point3.y);
		scene->addLine(point1.x, point1.y, point3.x, point3.y);
	}
}
