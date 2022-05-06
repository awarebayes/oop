//
// Created by dev on 5/1/22.
//
#include "object/inc/mesh_model.h"

void MeshModel::accept(Visitor& visitor)
{
	visitor.visit(*this);
}

const std::vector<Vertex> &MeshModel::get_vertices() const
{
	return vertices;
}

const std::vector<Line> &MeshModel::get_lines() const
{
	return lines;
}

MeshModel::MeshModel(std::vector<Vertex> vertices, std::vector<Line> lines)  : vertices(std::move(vertices)), lines(std::move(lines))
{
	_transform = Identity().share();
}
