//
// Created by dev on 5/3/22.
//

#ifndef INC_3_DRAW_VISITOR_H
#define INC_3_DRAW_VISITOR_H

#include <drawer/inc/base_canvas.h>
#include <memory>
#include <scene/inc/scene_group.h>
#include <object/inc/model_ref.h>
#include <object/inc/camera.h>
#include <scene/inc/scene.h>

#include "visitor/inc/base_visitor.h"

class DrawVisitor : public Visitor
{
private:
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<Camera> camera;
	Matrix4 context = Matrix4(1.0f);
	void clear_transform_context();
	void add_transform_context(const Matrix4 &ctx);
public:
	DrawVisitor(std::shared_ptr<Canvas> canvas, std::shared_ptr<Camera> camera);
	void visit(Camera &camera) override;
	void visit(SceneGroup &group) override;
	void visit(Scene &scene) override;
	void visit(MeshModelReference &ref) override;
	void visit(LightSource &lightSource);
};




#endif //INC_3_DRAW_VISITOR_H
