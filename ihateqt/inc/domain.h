//
// Created by dev on 3/9/22.
//

#ifndef IHATEQT_DOMAIN_H
#define IHATEQT_DOMAIN_H

#include "transformations.h"
#include "error.h"
#include "mishalib.h"
#include "scene_wrapper.h"
#include "obj3d.h"
#include "transformable_object.h"

enum class command_type
{
	load_object,
	save_object,
	draw_object,
	mutate_transforms,
};


typedef struct command
{
	big_string obj_path{};
	transform_mutation mutation{};
	domain_scene scene{};
	command_type type{};
} command;




errc entry_point(command &command);

#endif //IHATEQT_DOMAIN_H
