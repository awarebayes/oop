//
// Created by dev on 5/2/22.
//


#include <load/inc/mesh_model_builder.h>
#include <optional>

void MeshModelBuilder::read_lines()
{
	std::optional<Line> maybe_line{};
	maybe_line = source.next_line();
	while (maybe_line.has_value())
	{
		lines.push_back(maybe_line.value());
		maybe_line = source.next_line();
	}
}

void MeshModelBuilder::read_vertices()
{
	std::optional<Vertex> maybe_vertex{};
	maybe_vertex = source.next_vertex();
	while (maybe_vertex.has_value())
	{
		vertices.push_back(maybe_vertex.value());
		maybe_vertex = source.next_vertex();
	}
}

MeshModelBuilder::MeshModelBuilder(const std::string &path) : source(path)
{
	//lines.reserve(256);
	//vertices.reserve(256);
}

std::shared_ptr<Model> MeshModelBuilder::collect()
{
	auto model = std::make_shared<MeshModel>(vertices, lines);
	std::shared_ptr<Model> ref = std::make_shared<MeshModelReference>(model);
	return ref;
}

std::shared_ptr<Model> MeshModelDirector::build_model()
{
	MeshModelBuilder builder = MeshModelBuilder(object_path);
	builder.read_vertices();
	builder.read_lines();
	return builder.collect();
}
