//
// Created by dev on 3/29/22.
//

#ifndef IHATEQT_OBJ3D_UTIL_H
#define IHATEQT_OBJ3D_UTIL_H
#include "obj3d.h"


errc line_from_obj_string(line &self, const big_string &in);

errc line_to_obj_string(big_string &out, const line &self);

errc line_flush(FILE *file, line &l);

errc obj3d_read_vertex(obj3d &object, const int vertex_number, const big_string &str);

errc obj3d_read_line(obj3d &object, const int line_number, const big_string &str);

errc obj3d_flush_vertex(FILE *file, const int index, const obj3d object);

errc obj3d_flush_line(FILE *file, const int index, const obj3d object);

obj3d obj3d_default_cube();

errc copy_lines(obj3d &dest, const obj3d &source);

errc copy_vertices(obj3d &dest, const obj3d &source);

#endif //IHATEQT_OBJ3D_UTIL_H
