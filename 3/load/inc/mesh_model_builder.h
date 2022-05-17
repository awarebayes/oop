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
	ObjFileMeshSource source;
	std::vector<Line> lines{};
	std::vector<Vertex> vertices{};
public:
	explicit MeshModelBuilder(const std::string &path);
	std::shared_ptr<Model> collect() override;
	void read_vertices();
	void read_lines();
};

class MeshModelDirector : public ModelDirector
{
private:
	std::string object_path;
public:
	explicit MeshModelDirector(std::string path) : object_path(std::move(path)) {};
	std::shared_ptr<Model> build_model() override;
};

#endif //INC_3_MESH_MODEL_BUILDER_H
