//
// Created by dev on 4/23/22.
//

#ifndef LAB2_COPY_MOVE_H
#define LAB2_COPY_MOVE_H

#include "gtest/gtest.h"
#include "ordered_set/ordered_set.h"
#include "tests/util.h"
#include <random>

TEST(CopyMove, Copy) {
	OrderedSet<int> a{1,2,3};
	OrderedSet<int> b = a;
	EXPECT_EQ(b, (OrderedSet<int>{1,2,3}));
}


TEST(CopyMove, Move) {
	OrderedSet<int> a{1,2,3};
	OrderedSet<int> b = std::move(a);
	EXPECT_EQ(b, (OrderedSet<int>{1,2,3}));
	// EXPECT_TRUE(a.empty());
}

#endif //LAB2_COPY_MOVE_H
