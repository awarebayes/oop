//
// Created by dev on 08/04/2022.
//

#include "inc/scene_wrapper.h"


void clear_scene(domain_scene scene)
{
	scene->clear();
}

void scene_draw_line(domain_scene scene, double x1, double y1, double x2, double y2)
{
	scene->addLine(x1, y1, x2, y2);
}

