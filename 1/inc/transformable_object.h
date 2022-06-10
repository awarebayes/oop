//
// Created by dev on 04/04/2022.
//

#ifndef IHATEQT_TRANSFORMABLE_OBJECT_H
#define IHATEQT_TRANSFORMABLE_OBJECT_H

#include "inc/mishalib.h"
#include "inc/obj3d.h"
#include "inc/transformations.h"
#include "inc/scene_wrapper.h"

typedef struct transformable_object
{
	obj3d model;
	transformations transforms;
} transformable_object;

errc trans_object_draw(domain_scene scene, const transformable_object &object);

errc trans_object_load(transformable_object &object, const big_string &path);

errc trans_object_save(const transformable_object &object, const big_string &path);

errc trans_object_mutate_transform(transformable_object &object, const transform_mutation mut);

errc trans_object_reset_transforms(transformable_object &object, int screen_width, int screen_height);

transformable_object default_cube();

#endif //IHATEQT_TRANSFORMABLE_OBJECT_H
