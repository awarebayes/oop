//
// Created by dev on 4/19/22.
//

#ifndef LAB2_REMOVAL_H
#define LAB2_REMOVAL_H


TEST(Removal, TypicalRemoval) {
	OrderedSet<int> a;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.remove(1);
	a.remove(2);
	EXPECT_EQ(a, (OrderedSet<int>{3,4}));
}

void check_removal_works(int n_init, int n_delete, int mod)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(0, mod);

	std::set<int> std_set = random_std_set(n_init, mod);
	OrderedSet<int> my_set = my_set_from_std(std_set);

	for (int i = 0; i < n_delete; i++)
	{
		int generated = distr(gen);
		if (std_set.contains(generated))
			std_set.erase(generated);
		my_set.discard(generated);
	}

	assert_sets_equal(my_set, std_set);
}

TEST(Removal, RandomRemovalMod100)
{
	check_removal_works(10, 10, 100);
}

TEST(Removal, RandomRemovalMod1000)
{
	check_removal_works(100, 50, 1000);
}
#endif //LAB2_REMOVAL_H
