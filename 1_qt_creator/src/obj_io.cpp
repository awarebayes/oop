//
// Created by dev on 3/7/22.
//

#include "inc/obj_io.h"
#include "inc/config.h"
#include <array>
#include <sstream>
#include <fstream>

struct MinMax
{
	double min;
	double max;
};

Transformations get_appropriate_transformations(const Mesh3D &object)
{
	Vec4 first = object.vertices[0];
	std::array<struct MinMax, 3> min_max_coords = {{{ first.x, first.x },
	                                                { first.y, first.y },
	                                                { first.z, first.z }}};
	for (const auto &point: object.vertices)
	{
		for (int i = 0; i < 3; i++)
		{
			struct MinMax &mm = min_max_coords[i];
			mm.min = std::min(point.at(i), mm.min);
			mm.max = std::max(point.at(i), mm.max);
		}
	}

	double max_coordinate_difference = 0;
	for (int i = 0; i < 3; i++)
	{
		const struct MinMax &mm = min_max_coords[i];
		double coordinate_difference = mm.max - mm.min;
		max_coordinate_difference = std::max(max_coordinate_difference, coordinate_difference);
	}

	int screen_dim = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
	double required_scale = screen_dim / max_coordinate_difference;

	required_scale *= 0.6; // чтобы не на весь экран было

	Transformations transformations = {
			.translate = {
					.x = (double) SCREEN_WIDTH / 2,
					.y = (double) SCREEN_HEIGHT / 2,
					.z = 0,
					.type = TransformType::Translate },
			.rotate{ .x = 0, .y = 0, .z = 180, .type = TransformType::Rotate },
			.scale = { .x = required_scale, .y = required_scale, .z = required_scale, .type = TransformType::Scale },
	};
	return transformations;
}

auto read_obj_file(const std::string &file_path) -> cpp::result<ReadResult, errc>
{
	std::stringstream ss;
	std::ifstream in_file(file_path.c_str());
	if (in_file.fail())
		return cpp::fail(errc::no_such_file_or_directory);

	Mesh3D mesh = {
			.vertices = std::vector<Vec4>(),
			.indexes = std::vector<Indexes>(),
	};
	Transformations transformations = {{ 0 },
	                                   { 0 },
	                                   { 0 }};

	errc error = errc::ok;
	bool found_transformations = false;

	std::string line;
	std::string prefix;

	while (std::getline(in_file, line) and error == errc::ok)
	{
		ss.clear();
		ss.str(line);
		prefix.clear();

		ss >> prefix;
		if (prefix == "##")
		{
			auto maybe_error = transformations.read_partial(line);
			if (maybe_error.has_error())
				error = maybe_error.error();
			else
				found_transformations = true;
		}

		if (prefix == "v")
		{
			auto maybe_vertex = Vec4::vertex_from_obj_string(line);
			if (maybe_vertex.has_error())
				error = maybe_vertex.error();
			else
				mesh.vertices.push_back(maybe_vertex.value());
		}
		else if (prefix == "f")
		{
			auto maybe_indices = Indexes::from_obj_string(line);
			if (maybe_indices.has_error())
				error = maybe_indices.error();
			else
				mesh.indexes.push_back(maybe_indices.value());
		}
	}

	if (not found_transformations and error == errc::ok)
		transformations = get_appropriate_transformations(mesh);

	if (error != errc::ok)
		return cpp::fail(error);
	return ReadResult{ .transformations = transformations, .mesh = mesh };
}

auto write_obj_file(const std::string &file_path, const Mesh3D &mesh,
                    const Transformations &transformations) -> cpp::result<void, errc>
{
	std::ofstream file;
	file.open(file_path.c_str(), std::ios::out);
	if (not file.is_open())
		return cpp::fail(errc::bad_file_descriptor);

	file << transformations.to_obj_string().value();

	for (const auto &vertex: mesh.vertices)
		file << vertex.to_obj_string().value() << "\n";

	for (const auto &index: mesh.indexes)
		file << index.to_obj_string().value() << "\n";

	file.close();
	return {};
}
