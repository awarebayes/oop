//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_STATE_H
#define INC_1_QT_CREATOR_STATE_H

#include "mesh3d.h"
#include "transformations.h"


typedef struct State
{
	Mesh3D current_object;
	Transformations transform;

	Mat4x4 get_transformation_matrix();
	State();
} State;

#endif //INC_1_QT_CREATOR_STATE_H
