//
// Created by dev on 5/3/22.
//

#ifndef INC_3_DRAW_VISITOR_H
#define INC_3_DRAW_VISITOR_H

#include <drawer/inc/base_canvas.h>
#include <memory>
#include <object/inc/mesh_model.h>
#include <scene/inc/visible_group.h>
#include <object/inc/model_ref.h>
#include <object/inc/camera.h>
#include <scene/inc/scene.h>

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
	void visit(MeshModelReference &ref) override;
private:
	void visit_with_new_transform(VisibleGroup &group, const glm::mat4 &transformation);
	void visit_with_new_transform(MeshModel &model, const glm::mat4 &transformation);
	void visit_with_new_transform(VisibleObject &object, const glm::mat4 &transform);
	void draw_model(MeshModel &model, const glm::mat4 &model_matrix);
};




#endif //INC_3_DRAW_VISITOR_H
