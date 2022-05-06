//
// Created by dev on 5/3/22.
//

#ifndef INC_3_TEST_DRAW_H
#define INC_3_TEST_DRAW_H

#include <scene/inc/scene.h>
#include "visitor/inc/draw_visitor.h"
#include "drawer/inc/test_canvas.h"
#include "object/inc/mesh_model.h"
#include "manager/inc/transform_manager.h"


TEST(Draw, TestSimpleDraw)
{
	auto canv = std::make_shared<TestCanvas>();
	auto cam = std::make_shared<Camera>();
	auto visitor = DrawVisitor(canv, cam);
	auto line = MeshModelLoader().load_model("./tests/res/simple_line.obj");
	line->accept(visitor);
	EXPECT_EQ(canv->lines[0], TestLine(-1, -1, 1, 1));
}

TEST(Draw, TestSimpleRotate)
{
	auto canv = std::make_shared<TestCanvas>();
	auto cam = std::make_shared<Camera>();
	auto visitor = DrawVisitor(canv, cam);
	auto line = MeshModelLoader().load_model("./tests/res/simple_line.obj");
	auto transform_manager = Transformer(*line);
	transform_manager.rotate(90, 0, 0);
	line->accept(visitor);
	EXPECT_EQ(canv->lines[0], TestLine(-1, 1, 1, -1));
}

TEST(Draw, TestDrawScene)
{
	auto canv = std::make_shared<TestCanvas>();
	auto cam = std::make_shared<Camera>();
	auto visitor = DrawVisitor(canv, cam);
	auto line1 = MeshModelLoader().load_model("./tests/res/simple_line.obj");
	auto line2 = MeshModelLoader().load_model("./tests/res/simple_line.obj");
	auto scene = Scene();
	auto transform_manager = Transformer(*line2);
	transform_manager.translate(100, 0, 0);
	int l1_id = scene.add_object(line1);
	int l2_id = scene.add_object(line2);
	scene.accept(visitor);
	EXPECT_EQ(canv->lines[0], TestLine(-1, -1, 1, 1));
	EXPECT_EQ(canv->lines[1], TestLine(99, -1, 101, 1));
	EXPECT_EQ(l1_id, 0);
	EXPECT_EQ(l2_id, 1);
}


#endif //INC_3_TEST_DRAW_H
