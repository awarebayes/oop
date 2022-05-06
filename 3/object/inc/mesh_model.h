//
// Created by dev on 5/1/22.
//

#ifndef INC_3_MESH_MODEL_H
#define INC_3_MESH_MODEL_H

#include "drawable_model.h"
#include <utility>
#include <vector>
#include "math/inc/linalg.h"
#include "visitor/inc/base_visitor.h"
#include "visitor/inc/draw_visitor.h"

typedef std::pair<int, int> Line;
typedef Vector<4> Vertex;

class MeshModel : public DrawableModel
{
private:
	std::vector<Vertex> vertices{};
	std::vector<Line> lines{};
	friend class DrawVisitor;
public:
	MeshModel(std::vector<Vertex> vertices, std::vector<Line> lines);
	void accept(Visitor& visitor);
	const std::vector<Vertex>& get_vertices() const;
	const std::vector<Line>& get_lines() const;
	bool is_mesh() override {return true;};
};



#endif //INC_3_MESH_MODEL_H
