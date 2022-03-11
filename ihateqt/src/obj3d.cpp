//
// Created by dev on 3/10/22.
//
#include <array>
#include <sstream>
#include <fstream>
#include "inc/obj3d.h"
#include "inc/config.h"

struct triplet
{
	int p1, p2, p3;
	triplet(int p1_, int p2_, int p3_);

	static errc triplet_from_obj_string(const std::string &in, struct triplet &result);
	int &operator[](int index);
};

errc triplet::triplet_from_obj_string(const std::string &in, triplet &result)
{
	triplet self = { 0, 0, 0 };
	int temp_int = 0;
	errc ec = errc::ok;
	std::stringstream ss(in);
	std::string is_face;

	ss >> is_face;
	if (is_face != "f")
		ec = errc::invalid_index_string_in_file;

	int counter = 0;
	int indexes_read = 0;


	while (ss >> temp_int and ec == errc::ok)
	{
		if (temp_int - 1 < 0)
			ec = errc::index_mismatch;

		if (counter == 0 and indexes_read < 3)
			self[indexes_read++] = temp_int - 1;
		while (ss.peek() == '/')
		{
			counter += 1;
			ss.ignore(1, '/');
		}
		if (ss.peek() == ' ')
		{
			counter = 0;
			ss.ignore(1, ' ');
		}
		if (ss.fail() and indexes_read < 3)
			ec = errc::invalid_index_string_in_file;
	}

	if (ec != errc::ok)
		return errc::bad_from_string_read;
	return errc::ok;
}

int &triplet::operator[](int index)
{
	switch (index)
	{
		case 0:
			return p1;
		case 1:
			return p2;
		case 2:
			return p3;
		default:
			return p3;
	}
}

triplet::triplet(int p1_, int p2_, int p3_)
{
	p1 = std::min(p1_, std::min(p2_, p3_));
	p3 = std::max(p1_, std::max(p2_, p3_));
	p2 = p1_ + p2_ + p3_ - p1 - p3;
}

obj3d obj3d::default_cube()
{
	obj3d result = {};
	result.vertices = {
			{ 1.000000,  -1.000000, -1.000000, 1 },
			{ 1.000000,  -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, -1.000000, 1 },
			{ 1.000000,  1.000000,  -0.999999, 1 },
			{ 0.999999,  1.000000,  1.000001,  1 },
			{ -1.000000, 1.000000,  1.000000,  1 },
			{ -1.000000, 1.000000,  -1.000000, 1 },
	};


	std::vector<struct triplet> indices = {
			{ 0, 1, 2 },
			{ 6, 5, 4 },
			{ 3, 4, 0 },
			{ 4, 5, 1 },
			{ 2, 6, 7 },
			{ 0, 3, 7 },
			{ 0, 1, 3 },
			{ 4, 7, 5 },
			{ 0, 4, 1 },
			{ 1, 5, 2 },
			{ 3, 2, 7 },
			{ 4, 0, 7 }};

	for (const auto &tri: indices)
	{
		line l1 = std::make_pair(tri.p1, tri.p2);
		line l2 = std::make_pair(tri.p1, tri.p3);
		line l3 = std::make_pair(tri.p2, tri.p3);
		result.lines.insert(l1);
		result.lines.insert(l2);
		result.lines.insert(l3);
	}
	result.center = {0, 0, 0};
	return result;
}

struct MinMax
{
	double min;
	double max;
};


errc appropriate_transformations(const obj3d &object, transformations &transforms)
{
	if (object.vertices.empty())
		return errc::invalid_argument;

	vec4 first = object.vertices[0];
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

	transforms = {
			.translate = {
					.x = (double) SCREEN_WIDTH / 2,
					.y = (double) SCREEN_HEIGHT / 2,
					.z = 0,
					.type = transform_type::Translate },
			.rotate{ .x = 0, .y = 0, .z = 180, .type = transform_type::Rotate },
			.scale = { .x = required_scale, .y = required_scale, .z = required_scale, .type = transform_type::Scale },
	};
	return errc::ok;
}

errc read_obj3d(obj3d &self, const std::string &path)
{
	std::stringstream ss;
	std::ifstream in_file(path.c_str());
	if (in_file.fail())
		return errc::no_such_file_or_directory;

	obj3d mesh = {
			.vertices = std::vector<vec4>(),
			.lines = std::set<line>(),
	};

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

		if (prefix == "v")
		{
			vec4 read_result{};
			error = vec4::vertex_from_obj_string(line, read_result);
			mesh.vertices.push_back(read_result);
		}
		else if (prefix == "f")
		{
			auto read_result = triplet(0,0,0);
			error = triplet::triplet_from_obj_string(line, read_result);
			auto l1 = std::make_pair(read_result.p1, read_result.p2);
			auto l2 = std::make_pair(read_result.p1, read_result.p3);
			auto l3 = std::make_pair(read_result.p2, read_result.p3);
			mesh.lines.insert(l1);
			mesh.lines.insert(l2);
			mesh.lines.insert(l3);
		}

		else if (prefix == "l")
		{

		}
	}

	if (error != errc::ok)
			self = mesh;
	return error;
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
