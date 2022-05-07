//
// Created by dev on 5/7/22.
//

#ifndef INC_3_TEST_MANAGERS_H
#define INC_3_TEST_MANAGERS_H

#include <manager/inc/test_draw_manager.h>
#include <manager/inc/scene_manager.h>
#include <manager/inc/load_manager.h>

TEST(Managers, TestDraw)
{
	auto scene_manager = SceneManagerCreator().get();
	auto draw_manager = TestDrawManagerCreator::get_test();
	auto load_manager = LoadManagerCreator().get();
	auto line1_id = load_manager->load_mesh_model("./tests/res/simple_line.obj");
	auto line2_id = load_manager->load_mesh_model("./tests/res/simple_line.obj");
	draw_manager->draw_scene();
	EXPECT_EQ(line1_id, 0);
	EXPECT_EQ(line2_id, 1);
}


TEST(Managers, TestClone)
{
	auto scene_manager = SceneManagerCreator().get();
	auto draw_manager = TestDrawManagerCreator::get_test();
	auto load_manager = LoadManagerCreator().get();
	auto line1_id = load_manager->load_mesh_model("./tests/res/simple_line.obj");
	auto scene = scene_manager->get_scene();
	auto line2_id = scene->clone_object(line1_id);
	draw_manager->draw_scene();
	EXPECT_EQ(line1_id, 2);
	EXPECT_EQ(line2_id, 3);
}

#endif //INC_3_TEST_MANAGERS_H
