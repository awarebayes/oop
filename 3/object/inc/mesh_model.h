//
// Created by dev on 5/1/22.
//

#ifndef INC_3_MESH_MODEL_H
#define INC_3_MESH_MODEL_H

#include <utility>
#include <vector>
#include "math/inc/glm_wrapper.h"

typedef std::pair<int, int> Line;
typedef Vector4 Vertex;

class MeshModel
{
private:
	std::vector<Vertex> vertices{};
	std::vector<Line> lines{};
	friend class DrawVisitor;
public:
	MeshModel(std::vector<Vertex> vertices, std::vector<Line> lines);
	const std::vector<Vertex>& get_vertices() const;
	const std::vector<Line>& get_lines() const;
};

#endif //INC_3_MESH_MODEL_H
