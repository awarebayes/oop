//
// Created by dev on 2/25/22.
//

#include <array>
#include <sstream>
#include <algorithm>
#include "inc/mesh3d.h"

Mesh3D Mesh3D::default_cube()
{
	std::vector<Vec4> vertices = {
			{ 1.000000,  -1.000000, -1.000000, 1 },
			{ 1.000000,  -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, -1.000000, 1 },
			{ 1.000000,  1.000000,  -0.999999, 1 },
			{ 0.999999,  1.000000,  1.000001,  1 },
			{ -1.000000, 1.000000,  1.000000,  1 },
			{ -1.000000, 1.000000,  -1.000000, 1 },
	};

	std::vector<Indexes> indices = {
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

	return { .vertices = vertices, .indexes = indices };
}

bool Mesh3D::can_draw() const
{
	bool can_render = !vertices.empty() and !indexes.empty();

	int max_index = -1;
	for (const auto &index: indexes)
		max_index = std::max(max_index, *std::max_element(index.index, index.index + 3));
	if (max_index >= vertices.size())
		can_render = false;

	return can_render;
}

auto Indexes::from_obj_string(const std::string &in) -> cpp::result<Indexes, errc>
{
	int temp_int = 0;
	errc error_code = errc::ok;
	std::stringstream ss(in);
	std::string is_face;

	ss >> is_face;
	if (is_face != "f")
		error_code = errc::invalid_index_string_in_file;

	int counter = 0;
	int indexes_read = 0;

	Indexes self = { 0, 0, 0 };

	while (ss >> temp_int and error_code == errc::ok)
	{
		if (temp_int - 1 < 0)
			error_code = errc::index_mismatch;

		if (counter == 0 and indexes_read < 3)
			self.index[indexes_read++] = temp_int - 1;
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
			error_code = errc::invalid_index_string_in_file;
	}

	if (error_code != errc::ok)
		return cpp::fail(error_code);
	return self;
}

auto Indexes::to_obj_string() const -> cpp::result<std::string, errc>
{
	std::stringstream ss;
	ss << "f " << index[0] + 1 << " " << index[1] + 1 << " " << index[2] + 1;
	return ss.str();
}
