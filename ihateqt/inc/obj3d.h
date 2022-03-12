//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_OBJ3D_H
#define IHATEQT_OBJ3D_H


#include <vector>
#include <set>
#include "linalg.h"
#include "error.h"
#include "transformations.h"

typedef std::pair<int, int> line;

typedef struct obj3d
{
	std::vector<vec4> vertices;
	std::set<line> lines;
	vec4 center{};

	static obj3d default_cube();
	static errc from_file(obj3d &self, const std::string &path);
	static errc to_file(const obj3d &objects, const std::string &path);
} obj3d;


errc line_from_obj_string(const std::string &line, std::pair<int, int> &self);


errc appropriate_transformations(const obj3d &object, transformations &transforms);

#endif //IHATEQT_OBJ3D_H
