//
// Created by dev on 4/19/22.
//

#ifndef LAB2_OPERATIONS_H
#define LAB2_OPERATIONS_H


void check_union_works(int set1_size, int set2_size, int mod)
{
	std::vector<int> std_set1 = random_std_vector(set1_size, mod);
	std::vector<int> std_set2 = random_std_vector(set2_size, mod);
	OrderedSet<int> my_set1 = my_set_from_std(std_set1);
	OrderedSet<int> my_set2 = my_set_from_std(std_set2);
	OrderedSet<int> my_res = my_set1.union_(my_set2);

	std::vector<int> std_res;


	std::set_union(std_set1.begin(), std_set1.end(),
	               std_set2.begin(), std_set2.end(),
	               std::back_inserter(std_res));

	assert_sets_equal(my_res, std_res);
}


void check_difference_works(int set1_size, int set2_size, int mod)
{
	std::vector<int> std_set1 = random_std_vector(set1_size, mod);
	std::vector<int> std_set2 = random_std_vector(set2_size, mod);

	std::sort(std_set1.begin(), std_set1.end());
	std::sort(std_set2.begin(), std_set2.end());

	OrderedSet<int> my_set1 = my_set_from_std(std_set1);
	OrderedSet<int> my_set2 = my_set_from_std(std_set2);
	OrderedSet<int> my_res = my_set1.difference(my_set2);
	std::vector<int> std_res;


	std::set_difference(std_set1.begin(), std_set1.end(),
	               std_set2.begin(), std_set2.end(),
	               std::back_inserter(std_res));

	std::sort(std_res.begin(), std_res.end());

	assert_sets_equal(my_res, std_res);
}


void check_symmetric_diff_works(int set1_size, int set2_size, int mod)
{
	std::vector<int> std_set1 = random_std_vector(set1_size, mod);
	std::vector<int> std_set2 = random_std_vector(set2_size, mod);
	std::sort(std_set1.begin(), std_set1.end());
	std::sort(std_set2.begin(), std_set2.end());
	OrderedSet<int> my_set1 = my_set_from_std(std_set1);
	OrderedSet<int> my_set2 = my_set_from_std(std_set2);
	OrderedSet<int> my_res = my_set1.sym_difference(my_set2);
	std::vector<int> std_res;


	std::set_symmetric_difference(std_set1.begin(), std_set1.end(),
	                    std_set2.begin(), std_set2.end(),
	                    std::back_inserter(std_res));

	assert_sets_equal(my_res, std_res);
}

void check_intersection_works(int set1_size, int set2_size, int mod)
{
	std::vector<int> std_set1 = random_std_vector(set1_size, mod);
	std::vector<int> std_set2 = random_std_vector(set2_size, mod);
	std::sort(std_set1.begin(), std_set1.end());
	std::sort(std_set2.begin(), std_set2.end());
	OrderedSet<int> my_set1 = my_set_from_std(std_set1);
	OrderedSet<int> my_set2 = my_set_from_std(std_set2);
	OrderedSet<int> my_res = my_set1.intersection(my_set2);

	std::vector<int> std_res;

	std::set_intersection(std_set1.begin(), std_set1.end(),
	               std_set2.begin(), std_set2.end(),
	               std::back_inserter(std_res));

	assert_sets_equal(my_res, std_res);
}

TEST(Operations, Union)
{
	check_union_works(100, 100, 1000);
	check_union_works(100, 1000, 10000);
	check_union_works(1000, 100, 10000);
}


TEST(Operations, Difference)
{
	check_difference_works(100, 100, 1000);
	check_difference_works(100, 1000, 10000);
	check_difference_works(1000, 100, 10000);
}


TEST(Operations, SymmetricDifference)
{
	check_symmetric_diff_works(100, 100, 1000);
	check_symmetric_diff_works(100, 1000, 10000);
	check_symmetric_diff_works(1000, 100, 10000);
}


TEST(Operations, Intersection)
{
	check_intersection_works(100, 100, 1000);
	check_intersection_works(100, 1000, 10000);
	check_intersection_works(1000, 100, 10000);
}

#endif //LAB2_OPERATIONS_H
