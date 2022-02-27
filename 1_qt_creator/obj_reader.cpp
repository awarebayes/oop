//
// Created by dev on 2/26/22.
//

#include "obj_reader.h"
#include <fstream>
#include <sstream>

Mesh3D read_obj_file(const std::string &filename)
{
	Mesh3D mesh = {
			.vertices = std::vector<Vec4>(),
			.indexes = std::vector<Indexes>(),
	};
	std::stringstream ss;
	std::ifstream in_file(filename);
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
