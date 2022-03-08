//
// Created by dev on 2/25/22.
//

#ifndef INC_1_QT_CREATOR_MESH3D_H
#define INC_1_QT_CREATOR_MESH3D_H

#include <vector>
#include <string>
#include "linalg.h"
#include "transformations.h"
#include "result.h"
#include "error.h"

typedef struct Indexes
{
	int index[3];

	static auto from_obj_string(const std::string &in) -> cpp::result<Indexes, errc>;

	auto to_obj_string() const -> cpp::result<std::string, errc>;

	int max;
} Indexes;

typedef struct Mesh3D
{
	std::vector<Vec4> vertices;
	std::vector<Indexes> indexes;

	static Mesh3D default_cube();

	bool can_draw() const;
} Mesh3D;

#endif //INC_1_QT_CREATOR_MESH3D_H
