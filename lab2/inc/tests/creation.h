//
// Created by dev on 4/19/22.
//

#ifndef LAB2_CREATION_H
#define LAB2_CREATION_H
#include "gtest/gtest.h"
#include "concrete_set.h"

TEST(Creation, Default) {
	OrderedSet<int> a;
	EXPECT_EQ(a.empty(), true);
}

TEST(Creation, ArgsList) {
	OrderedSet<int> a{1, 2, 3, 4};
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
	EXPECT_EQ(a.size(), 4);
}

TEST(Creation, Copy) {
	OrderedSet<int> a{1, 2, 3, 4};
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
	OrderedSet<int> b = a;
	EXPECT_EQ(b, (OrderedSet<int>{1,2,3,4}));
}

TEST(Creation, DublicateArgs) {
	OrderedSet<int> a{1, 1, 1, 2, 3, 4, 4};
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}

#endif //LAB2_CREATION_H
