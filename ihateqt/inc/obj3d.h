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
} obj3d;

errc read_obj3d(obj3d &self, const std::string &path);

errc save_transformed_obj3d(const obj3d &object, const transformations &transforms, const std::string &path);

errc appropriate_scale_obj3d(obj3d &object);

#endif //IHATEQT_OBJ3D_H
