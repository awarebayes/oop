//
// Created by dev on 3/29/22.
//

#ifndef IHATEQT_OBJ3D_UTIL_H
#define IHATEQT_OBJ3D_UTIL_H
#include "obj3d.h"


errc line_from_obj_string(line &self, const big_string &in);

errc line_to_obj_string(big_string &out, const line &self);

errc find_scale_to_fit_screen(double &out_scale, const obj3d &object);

errc apply_scale_to_object(obj3d &object, const double scale);

errc scale_to_fit_screen(obj3d &object);

errc find_mean(vec4 &center, const vec4 *vertices, const int n_vertices);

errc center_object_at_zero(obj3d &object);

errc obj3d_read_vertex(obj3d &object, const int vertex_number, const big_string &str);

errc obj3d_read_line(obj3d &object, const int line_number, const big_string &str);

obj3d obj3d_default_cube();

errc copy_lines(obj3d &dest, const obj3d &source);

#endif //IHATEQT_OBJ3D_UTIL_H
