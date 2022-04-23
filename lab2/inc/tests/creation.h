//
// Created by dev on 4/19/22.
//

#ifndef LAB2_CREATION_H
#define LAB2_CREATION_H
#include "gtest/gtest.h"
#include "ordered_set/ordered_set.h"
#include "ordered_set/ordered_set.hpp"

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


TEST(Creation, CArray) {
	int arr[] = {1, 2, 3, 4};
	OrderedSet<int> a = OrderedSet(arr, 4);
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}

TEST(Creation, StdVector) {
	std::vector<int> vec = {1, 2, 3, 4};
	OrderedSet<int> a = OrderedSet(vec);
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}

TEST(Creation, StdSet) {
	std::set<int> set = {1, 2, 3, 4};
	OrderedSet<int> a = OrderedSet(set);
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}

TEST(Creation, StdSetIterator) {
	std::set<int> set = {1, 2, 3, 4};
	OrderedSet<int> a = OrderedSet<int>(std::begin(set), std::end(set));
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}




#endif //LAB2_CREATION_H
