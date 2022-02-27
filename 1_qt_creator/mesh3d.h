//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_MESH3D_H
#define INC_1_QT_CREATOR_MESH3D_H
#include <vector>
#include <string>
//#include "state.h"
#include "linalg.h"
#include "transformations.h"

typedef struct Indexes
{
	int index[3];
} Indexes;

typedef struct Mesh3D
{
	std::vector<Vec4> vertices;
	std::vector<Indexes> indexes;

	static Mesh3D from_file(std::string obj_path);
	static Mesh3D default_cube();
	Transformations get_appropriate_transformations();
} Mesh3D;

#endif //INC_1_QT_CREATOR_MESH3D_H
