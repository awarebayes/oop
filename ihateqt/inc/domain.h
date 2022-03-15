//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_DOMAIN_H
#define IHATEQT_DOMAIN_H

#include <QGraphicsScene>
#include "transformations.h"
#include "error.h"
#include "obj3d.h"
#include "mishalib.h"

enum class command_type
{
	load_object,
	save_object,
	draw_object,
	default_view,
};

typedef struct state
{
	big_string obj_path{};
    transformations transforms{};
	obj3d object{};
	QGraphicsScene *scene;
	bool just_initialized = false;
} state;


errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms);

errc entry_point(command_type command, state &current_state);

errc load_object_and_transforms(obj3d &object, transformations &transforms, const big_string &path);

errc save_object_and_transforms(const obj3d &object, const transformations &transforms, const big_string &path);

#endif //IHATEQT_DOMAIN_H
