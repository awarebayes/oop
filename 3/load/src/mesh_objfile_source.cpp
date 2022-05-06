//
// Created by dev on 5/2/22.
//

#include <load/inc/mesh_objfile_source.h>

ObjFileMeshSource::ObjFileMeshSource(const std::string &path)
{
	in_file = std::ifstream(path);
	if (in_file.fail())
		throw std::runtime_error("Could not open file");
}

template<typename T>
T vector_pop_first(std::vector<T> &vec)
{
	auto last_elem = vec[0];
	vec.erase(vec.begin());
	return last_elem;
}

std::optional<Line> ObjFileMeshSource::next_line()
{
	while (line_buffer.empty() and !in_file.eof())
		iter_file_line();
	if (line_buffer.empty())
		return std::nullopt;
	return vector_pop_first(line_buffer);
}

std::optional<Vertex> ObjFileMeshSource::next_vertex()
{
	while (vertex_buffer.empty() and !in_file.eof())
		iter_file_line();
	if (vertex_buffer.empty())
		return std::nullopt;
	return vector_pop_first(vertex_buffer);
}

void ObjFileMeshSource::iter_file_line()
{
	std::string buffer{};
	std::string prefix{};
	std::stringstream ss{};
	std::getline(in_file, buffer);
	ss.str(buffer);
	ss >> prefix;

	if (prefix == "l")
		read_line(ss);

	if (prefix == "v")
		read_vertex(ss);
}

void ObjFileMeshSource::read_vertex(std::stringstream &ss)
{
	Vertex vertex{0, 0, 0, 1};
	ss >> vertex(0) >> vertex(1) >> vertex(2);
	if (ss.fail())
		throw std::runtime_error("unable to read line");
	vertex_buffer.push_back(vertex);
}

void ObjFileMeshSource::read_line(std::stringstream &ss)
{
	Line line{};
	ss >> line.first >> line.second;
	if (ss.fail())
		throw std::runtime_error("unable to read line");
	line_buffer.push_back(line);
}



