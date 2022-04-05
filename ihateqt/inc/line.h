//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_LINE_H
#define IHATEQT_LINE_H
#include "inc/error.h"
#include "inc/mishalib.h"
#include "inc/scene_wrapper.h"
#include "inc/linalg.h"

typedef struct line
{
	int first, second;
} line;

errc line_from_obj_string(line &self, const big_string &in);

errc line_to_obj_string(big_string &out, const line &self);

errc line_flush(FILE *file, line &l);

errc draw_line(domain_scene scene, vec4 point1, vec4 point2);

#endif