//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_OBJ3D_H
#define IHATEQT_OBJ3D_H


#include <vector>
#include <set>
#include <QGraphicsScene>
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

errc init_obj3d(obj3d &self, const int n_vertices, const int n_lines);

errc free_obj3d(obj3d &self);

obj3d obj3d_default_cube();

errc obj3d_from_file(obj3d &dest, const big_string path);

errc obj3d_to_file(const obj3d &object, const big_string &path);

errc obj3d_apply_transform_then_copy(obj3d &dest, const obj3d &source, const transformations &transforms);

errc obj3d_draw(QGraphicsScene *scene, const obj3d &object);

errc obj3d_move_if_ok(obj3d &dest, obj3d &source, const errc ec);


#endif //IHATEQT_OBJ3D_H
