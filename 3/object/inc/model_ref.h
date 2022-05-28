//
// Created by dev on 5/7/22.
//

#ifndef INC_3_MODEL_REF_H
#define INC_3_MODEL_REF_H

#include <utility>

#include "object/inc/scene_object.h"
#include "drawable_model.h"
#include "mesh_model.h"

class MeshModelReference : public Model
{
private:
	std::shared_ptr<MeshModel> base;
	friend class DrawVisitor;
public:
	explicit MeshModelReference(std::shared_ptr<MeshModel>  ref) : base(std::move(ref)) {};
	~MeshModelReference() override = default;
	void accept(Visitor& v) override { v.visit(*this); };
	// todo friend visitor
};

#endif