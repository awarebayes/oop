//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_OBJ3D_H
#define IHATEQT_OBJ3D_H

#include "linalg.h"
#include "error.h"
#include "transformations.h"
#include "mishalib.h"
#include "line.h"
#include "scene_wrapper.h"

typedef struct
{
	vec4 *vertices = nullptr;
	line *lines = nullptr;
	int n_vertices = 0;
	int n_lines = 0;
} obj3d;

errc init_obj3d(obj3d &self, const int n_vertices, const int n_lines);

errc free_obj3d(obj3d &self);

obj3d obj3d_default_cube();

errc obj3d_from_file(obj3d &dest, const big_string path);

errc obj3d_to_file(const obj3d &object, const big_string &path);

errc obj3d_apply_transform_then_copy(obj3d &dest, const obj3d &source, const transformations &transforms);

errc obj3d_draw(domain_scene scene, const obj3d &object);

errc obj3d_draw_line(domain_scene &scene, const obj3d &object, const int line_num);

errc obj3d_get_points(vec4 &p1, vec4 &p2, const obj3d &object, const line line_map);

errc obj3d_copy(obj3d &dest, const obj3d &source);

errc obj3d_apply_transform(obj3d &dest, const transformations &transforms);

#endif //IHATEQT_OBJ3D_H
