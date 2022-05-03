//
// Created by dev on 5/2/22.
//

#ifndef INC_3_MESH_OBJFILE_SOURCE_H
#define INC_3_MESH_OBJFILE_SOURCE_H

#include "load/inc/mesh_model_source.h"
#include <fstream>
#include <sstream>

class ObjFileMeshSource : public MeshModelSource
{
private:
	std::ifstream in_file{};
	std::vector<Line> line_buffer{};
	std::vector<Vertex> vertex_buffer{};
	void read_vertex(std::stringstream &ss);
	void read_line(std::stringstream &ss);
	void iter_file_line();
public:
	explicit ObjFileMeshSource(const std::string& path);
	std::optional<Line> next_line() override;
	std::optional<Vertex> next_vertex() override;
};

#endif //INC_3_MESH_OBJFILE_SOURCE_H
