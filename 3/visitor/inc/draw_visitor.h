//
// Created by dev on 5/3/22.
//

#ifndef INC_3_DRAW_VISITOR_H
#define INC_3_DRAW_VISITOR_H

#include <scene/inc/canvas.h>
#include <memory>
#include <object/inc/mesh_model.h>
#include <object/inc/camera.h>

#include "visitor/inc/base_visitor.h"

class DrawVisitor : public Visitor
{
private:
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<Camera> camera;
public:
	DrawVisitor(std::shared_ptr<Canvas> canvas, std::shared_ptr<Camera> camera);
	void visit(Camera &camera) override;
	void visit(VisibleGroup &group) override;
	void visit(MeshModel &model) override;
	void visit(Scene &scene) override;
	void visit(VisibleObject &object) override;

};




#endif //INC_3_DRAW_VISITOR_H
