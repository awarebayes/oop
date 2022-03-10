//
// Created by dev on 3/10/22.
//
#include <array>
#include "inc/obj3d.h"

struct index_t
{
	int p1, p2, p3;
	index_t(int p1_, int p2_, int p3_)
	{
		p1 = std::min(p1_, std::min(p2_, p3_));
		p3 = std::max(p1_, std::max(p2_, p3_));
		p2 = p1_ + p2_ + p3_ - p1 - p3;
	}
};

obj3d obj3d::default_cube()
{
	obj3d result = {};
	result.vertices = {
			{ 1.000000,  -1.000000, -1.000000, 1 },
			{ 1.000000,  -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, 1.000000,  1 },
			{ -1.000000, -1.000000, -1.000000, 1 },
			{ 1.000000,  1.000000,  -0.999999, 1 },
			{ 0.999999,  1.000000,  1.000001,  1 },
			{ -1.000000, 1.000000,  1.000000,  1 },
			{ -1.000000, 1.000000,  -1.000000, 1 },
	};


	std::vector<struct index_t> indices = {
			{ 0, 1, 2 },
			{ 6, 5, 4 },
			{ 3, 4, 0 },
			{ 4, 5, 1 },
			{ 2, 6, 7 },
			{ 0, 3, 7 },
			{ 0, 1, 3 },
			{ 4, 7, 5 },
			{ 0, 4, 1 },
			{ 1, 5, 2 },
			{ 3, 2, 7 },
			{ 4, 0, 7 }};

	for (const auto &triplet: indices)
	{
		line l1 = std::make_pair(triplet.p1, triplet.p2);
		line l2 = std::make_pair(triplet.p1, triplet.p3);
		line l3 = std::make_pair(triplet.p2, triplet.p3);
		result.lines.insert(l1);
		result.lines.insert(l2);
		result.lines.insert(l3);
	}
	result.center = {0, 0, 0};
	return result;
}
