//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_DOMAIN_H
#define IHATEQT_DOMAIN_H

#include <string>
#include <QGraphicsScene>
#include "transformations.h"
#include "error.h"
#include "obj3d.h"

enum class command_type
{
	load_object,
	save_object,
	draw_object,
};

typedef struct state
{
	std::string obj_path{};
    transformations transforms{};
	obj3d object{};
	QGraphicsScene *scene;
	bool just_initialized = false;
} state;


errc draw_object(QGraphicsScene *scene, const obj3d &object, const transformations &transforms);

errc entry_point(command_type command, state &current_state);


#endif //IHATEQT_DOMAIN_H
