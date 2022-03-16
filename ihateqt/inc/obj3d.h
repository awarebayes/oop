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
	vec4 *vertices = nullptr;
	line *lines = nullptr;
	int n_vertices = 0;
	int n_lines = 0;

} obj3d;

errc free_obj3d(obj3d &self);

errc line_from_obj_string(const big_string &in, line &self);

obj3d obj3d_default_cube();

errc obj3d_from_file(obj3d &out_obj, const big_string path);

errc obj3d_to_file(const obj3d &self, const big_string &path);

static errc find_object_center(vec4 &center, const obj3d &object);

static errc center_object_at_zero(obj3d &self);

errc copy_transformed_vertices(vec4 *dest, const transformations &transforms, const obj3d &object);

errc scale_to_fit_screen(obj3d &object);

#endif //IHATEQT_OBJ3D_H
