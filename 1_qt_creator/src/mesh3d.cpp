//
// Created by dev on 2/25/22.
//

#include <array>
#include <ranges>
#include <sstream>
#include <fstream>
#include "inc/mesh3d.h"
#include "inc/model.h"
#include "inc/config.h"


Mesh3D Mesh3D::default_cube()
{
	std::vector<Vec4> vertices = {
			{1.000000, -1.000000, -1.000000, 1},
			{1.000000, -1.000000, 1.000000, 1},
			{-1.000000, -1.000000, 1.000000, 1},
			{-1.000000, -1.000000, -1.000000, 1},
			{1.000000, 1.000000, -0.999999, 1},
			{0.999999, 1.000000, 1.000001, 1},
			{-1.000000, 1.000000, 1.000000, 1},
			{-1.000000, 1.000000, -1.000000, 1},
	};

	std::vector<Indexes> indices = {
			{0, 1, 2},
			{6, 5, 4},
			{3, 4, 0},
			{4, 5, 1},
			{2, 6, 7},
			{0, 3, 7},
			{0, 1, 3},
			{4, 7, 5},
			{0, 4, 1},
			{1, 5, 2},
			{3, 2, 7},
			{4, 0, 7}
	};

	return {.vertices=vertices, .indexes=indices};
}

struct MinMax {
	double min;
	double max;
};

Transformations Mesh3D::get_appropriate_transformations() const
{
	Vec4 first = vertices[0];
	std::array<struct MinMax, 3> min_max_coords = {{
			                                                     { first.x, first.x },
			                                                     { first.y, first.y },
			                                                     { first.z, first.z }
	                                                     }};
	for (const auto &point: vertices)
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
					.x = (double)SCREEN_WIDTH / 2,
					.y = (double) SCREEN_HEIGHT / 2,
					.z = 0,
			},
			.rotate {0,0,180},
			.scale = {
					.x = required_scale,
					.y = required_scale,
					.z = required_scale,
			},
	};
	return transformations;
}

Mesh3D Mesh3D::from_file(const std::string &obj_path)
{

	Mesh3D mesh = {
			.vertices = std::vector<Vec4>(),
			.indexes = std::vector<Indexes>(),
	};
	std::stringstream ss;
	std::ifstream in_file(obj_path.c_str());
	if (in_file.fail())
		return mesh;

	std::string line;
	std::string prefix;

	int temp_int = 0;

	while (std::getline(in_file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "v")
		{
			Vec4 temp = {0, 0, 0, 1};
			ss >> temp.x >> temp.y >> temp.z;
			mesh.vertices.push_back(temp);
		}

		else if (prefix == "f")
		{
			int counter = 0;
			int indexes_read = 0;
			Indexes indices = {0, 0, 0};
			while (ss >> temp_int)
			{
				if (counter == 0 and indexes_read < 3)
					indices.index[indexes_read++] = temp_int - 1;
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
			}
			mesh.indexes.push_back(indices);
		}
	}
	return mesh;
}

bool Mesh3D::is_empty()
{
	return indexes.empty() || vertices.empty();
}
