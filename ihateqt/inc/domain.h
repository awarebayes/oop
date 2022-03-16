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

typedef struct command
{
	transformations transforms{};
	big_string obj_path{};
	QGraphicsScene *scene{};
	command_type type;
} command;


errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms);

errc entry_point(command &command);

errc load_object(obj3d &object, const big_string &path);

errc save_object(const obj3d &object, const transformations &transforms, const big_string &path);

#endif //IHATEQT_DOMAIN_H
