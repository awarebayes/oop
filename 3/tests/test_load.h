//
// Created by dev on 5/2/22.
//

#ifndef INC_3_TEST_LOAD_H
#define INC_3_TEST_LOAD_H


#include "gtest/gtest.h"
#include "load/inc/mesh_objfile_source.h"
#include "load/inc/mesh_model_loader.h"

bool operator==(const Line &l1, const Line &l2)
{
	return l1.first == l2.first && l1.second == l2.second;
}

TEST(Load, TestReadLines)
{
	ObjFileMeshSource source("./tests/res/dummy_objfile.obj");
	std::optional<Line> maybe_line{};
	std::optional<Vertex> maybe_Vertex{};
	Line l1{1, 2};
	Line l2{3, 4};
	Line l3{4, 5};
	maybe_line = source.next_line();
	EXPECT_TRUE(maybe_line.has_value());
	EXPECT_EQ(maybe_line.value(), l1);
	maybe_line = source.next_line();
	EXPECT_EQ(maybe_line.value(), l2);
	EXPECT_TRUE(maybe_line.has_value());
	maybe_line = source.next_line();
	EXPECT_TRUE(maybe_line.has_value());
	EXPECT_EQ(maybe_line.value(), l3);
	maybe_line = source.next_line();
	EXPECT_FALSE(maybe_line.has_value());
}


TEST(Load, TestReadObject)
{
	MeshModelLoader().load_model("./tests/res/dummy_objfile.obj");
}

#endif //INC_3_TEST_LOAD_H
