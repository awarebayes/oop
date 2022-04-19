//
// Created by dev on 4/19/22.
//

#ifndef LAB2_UTIL_H
#define LAB2_UTIL_H

#include "gtest/gtest.h"
#include "concrete_set.h"
#include <random>

OrderedSet<int> random_my_set(int target_size, int mod)
{
	assert(mod >= target_size);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<int> distr(0, mod); // define the range
	OrderedSet<int> my_set;

	while(my_set.size() < target_size)
	{
		int generated = distr(gen);
		my_set.insert(generated);
	}
	return my_set;
}


std::set<int> random_std_set(int target_size, int mod)
{
	assert(mod >= target_size);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<int> distr(0, mod); // define the range
	std::set<int> my_set;

	while(my_set.size() < target_size)
	{
		int generated = distr(gen);
		my_set.insert(generated);
	}
	return my_set;
}


std::vector<int> random_std_vector(int target_size, int mod)
{
	assert(mod >= target_size);
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<int> distr(0, mod); // define the range
	std::vector<int> my_set;

	while(my_set.size() < target_size)
	{
		int generated = distr(gen);
		if (std::find(my_set.begin(), my_set.end(), generated) == my_set.end())
			my_set.push_back(generated);
	}
	return my_set;
}

OrderedSet<int> my_set_from_std(std::set<int> &std_set)
{
	OrderedSet<int> result;
	for (auto elem: std_set)
		result.insert(elem);
	return result;
}

OrderedSet<int> my_set_from_std(std::vector<int> &std_set)
{
	OrderedSet<int> result;
	for (auto elem: std_set)
		result.insert(elem);
	return result;
}

void assert_sets_equal(OrderedSet<int> &my_set, std::set<int> &std_set)
{
	for (auto elem: std_set)
	{
		EXPECT_TRUE(my_set.contains(elem));
	}

	for (auto elem: my_set)
	{
		EXPECT_TRUE(std_set.contains(elem));
	}
}



void assert_sets_equal(OrderedSet<int> &my_set, std::vector<int> &std_set)
{
	for (auto elem: std_set)
	{
		EXPECT_TRUE(my_set.contains(elem));
	}

	for (auto elem: my_set)
	{
		EXPECT_TRUE(std::find(std_set.begin(), std_set.end(), elem) != std_set.end());
	}
}

#endif //LAB2_UTIL_H
