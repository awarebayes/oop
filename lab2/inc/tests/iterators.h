//
// Created by dev on 4/23/22.
//

#ifndef LAB2_ITERATORS_H
#define LAB2_ITERATORS_H

TEST(Iterators, ForLoop)
{
	OrderedSet<int> a{ 1, 2, 3, 4 };
	auto iter = a.begin();
	EXPECT_EQ(*iter, 1);
	iter++;
	EXPECT_EQ(*iter, 2);
	iter++;
	EXPECT_EQ(*iter, 3);
	iter++;
	EXPECT_EQ(*iter, 4);
	iter++;
	EXPECT_EQ(iter, a.end());
	EXPECT_THROW(iter++, IterationStoppedError);
}


TEST(Iterators, Find)
{
	OrderedSet<int> a{ 1, 2, 3, 4 };
	auto iter = a.find(1);
	EXPECT_EQ(iter, a.begin());
	auto iter2 = a.find(7);
	EXPECT_EQ(iter2, a.end());
}

#endif //LAB2_ITERATORS_H
