//
// Created by dev on 4/19/22.
//

#ifndef LAB2_INSERTION_H
#define LAB2_INSERTION_H

#include "gtest/gtest.h"
#include "ordered_set/ordered_set.h"
#include "tests/util.h"
#include <random>

TEST(Insertion, TypicalInsertion) {
	OrderedSet<int> a;
	a.insert(1);
	a.insert(1);
	a.insert(1);
	a.insert(2);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	EXPECT_EQ(a, (OrderedSet<int>{1,2,3,4}));
}

void check_insertion_works(int n_trials, int mod)
{
	std::set<int> std_set = random_std_set(n_trials, mod);
	OrderedSet<int> my_set = my_set_from_std(std_set);
	assert_sets_equal(my_set, std_set);
}

TEST(Insertion, RandomInsertionMod100)
{
	check_insertion_works(100, 100);
}

TEST(Insertion, RandomInsertionMod1000)
{
	// check_insertion_works(1000, 100);
}

TEST(Insertion, OperatorInsertion)
{
	OrderedSet<int> a;
	OrderedSet<int> b = (a + 1 + 2 + 3 + 1 + 4);
	EXPECT_EQ(b.size(), 4);
	EXPECT_EQ(b, (OrderedSet<int>{1,2,3,4}));
	EXPECT_EQ(a, (OrderedSet<int>{}));
}

#endif //LAB2_INSERTION_H
