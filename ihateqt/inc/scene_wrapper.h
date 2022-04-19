//
// Created by dev on 04/04/2022.
//

#ifndef IHATEQT_SCENE_WRAPPER_H
#define IHATEQT_SCENE_WRAPPER_H

#include <QGraphicsScene>

typedef struct QGraphicsScene *domain_scene;

void clear_scene(domain_scene scene);
void scene_draw_line(domain_scene scene, double x1, double y1, double x2, double y2);

#endif //IHATEQT_SCENE_WRAPPER_H
