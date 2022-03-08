//
// Created by dev on 3/7/22.
//

#ifndef INC_1_QT_CREATOR_OBJ_IO_H
#define INC_1_QT_CREATOR_OBJ_IO_H

#include <optional>
#include "mesh3d.h"
#include "transformations.h"
#include "result.h"

struct ReadResult
{
	Transformations transformations;
	Mesh3D mesh;
};

auto read_obj_file(const std::string &file_path) -> cpp::result<ReadResult, errc>;

auto write_obj_file(
		const std::string &file_path,
		const Mesh3D &mesh,
		const Transformations &transformations)
-> cpp::result<void, errc>;

Transformations get_appropriate_transformations(const Mesh3D &object);

#endif //INC_1_QT_CREATOR_OBJ_IO_H
