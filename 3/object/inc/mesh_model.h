//
// Created by dev on 5/1/22.
//

#ifndef INC_3_MESH_MODEL_H
#define INC_3_MESH_MODEL_H

#include "drawable_model.h"
#include <utility>
#include <vector>
#include "math/inc/linalg.h"

class Line
{
public:
	int first = 0;
	int second = 0;
};

typedef Vector<4> Vertex;

class MeshModel : public DrawableModel
{
private:
	std::vector<Vertex> vertices{};
	std::vector<Line> lines{};
public:
	MeshModel(std::vector<Vertex> vertices, std::vector<Line> lines) : vertices(std::move(vertices)), lines(std::move(lines)) {};
	void draw(std::unique_ptr<Canvas> &canvas) const override;
};



#endif //INC_3_MESH_MODEL_H
