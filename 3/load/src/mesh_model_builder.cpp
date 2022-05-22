//
// Created by dev on 5/2/22.
//


#include <load/inc/mesh_model_builder.h>
#include <optional>
#include <exception/loader_exceptions.h>

void MeshModelBuilder::read_lines()
{
	std::optional<Line> maybe_line{};
	maybe_line = source->next_line();
	while (maybe_line.has_value())
	{
		lines.push_back(maybe_line.value());
		maybe_line = source->next_line();
	}
}

void MeshModelBuilder::read_vertices()
{
	std::optional<Vertex> maybe_vertex{};
	maybe_vertex = source->next_vertex();
	while (maybe_vertex.has_value())
	{
		vertices.push_back(maybe_vertex.value());
		maybe_vertex = source->next_vertex();
	}
}

MeshModelBuilder::MeshModelBuilder(std::unique_ptr<MeshModelSource> source_)
{
	source = std::move(source_);
	//lines.reserve(256);
	//vertices.reserve(256);
}

std::unique_ptr<MeshModelReference> MeshModelBuilder::get_result()
{
	auto model = std::make_shared<MeshModel>(vertices, lines);
	return std::make_unique<MeshModelReference>(model);
}

void MeshModelDirector::build_model()
{
	if (builder == nullptr)
		throw NoBuilderError(__FILE__, __LINE__, "You need to provide a builder");
	builder->read_vertices();
	builder->read_lines();
}

void MeshModelDirector::set_builder(std::shared_ptr<MeshModelBuilder> builder_)
{
	builder = builder_;
}
