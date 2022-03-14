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
#include "mishalib.h"

typedef struct line
{
	int first, second;
} line;

typedef struct obj3d
{
	vec4 center{};
	vec4 *vertices = nullptr;
	line *lines = nullptr;
	int n_vertices = 0;
	int n_lines = 0;

} obj3d;

errc new_obj3d(int n_vertices, int n_lines);

errc free_obj3d(obj3d &self);

errc line_from_obj_string(const string512 &line, line &self);

obj3d default_cube();

errc obj3d_from_file(obj3d &self, const string512 &path);

errc obj3d_to_file(const obj3d &self, const string512 &path);

errc appropriate_transformations(const obj3d &object, transformations &transforms);

#endif //IHATEQT_OBJ3D_H
