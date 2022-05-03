//
// Created by dev on 5/2/22.
//

#ifndef INC_3_MESH_MODEL_SOURCE_H
#define INC_3_MESH_MODEL_SOURCE_H

#include "object/inc/mesh_model.h"
#include <optional>

class MeshModelSource
{
public:
	virtual std::optional<Line> next_line() = 0;
	virtual std::optional<Vertex> next_vertex() = 0;
};

#endif //INC_3_MESH_MODEL_SOURCE_H
