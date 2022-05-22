//
// Created by dev on 5/2/22.
//

#ifndef INC_3_MESH_MODEL_BUILDER_H
#define INC_3_MESH_MODEL_BUILDER_H

#include <utility>
#include <list>

#include "load/inc/abstract.h"
#include "load/inc/mesh_objfile_source.h"
#include "object/inc/mesh_model.h"
#include "object/inc/model_ref.h"

class MeshModelBuilder : public ModelBuilder
{
private:
	std::unique_ptr<MeshModelSource> source; // accept loader here
	std::vector<Line> lines{};
	std::vector<Vertex> vertices{};
public:
	explicit MeshModelBuilder(std::unique_ptr<MeshModelSource> source);
	std::unique_ptr<MeshModelReference> get_result();
	void read_vertices() override;
	void read_lines() override;
};

class MeshModelDirector : public ModelDirector
{
private:
	std::shared_ptr<MeshModelBuilder> builder{};
public:
	explicit MeshModelDirector() = default;
	void set_builder(std::shared_ptr<MeshModelBuilder> builder_);
	void build_model() override;
};

#endif //INC_3_MESH_MODEL_BUILDER_H
