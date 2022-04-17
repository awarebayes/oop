//
// Created by dev on 4/16/22.
//

#ifndef LAB2_MY_SET_H
#define LAB2_MY_SET_H

#include "abstract_set.h"
#include "abstract_set.hpp"
#include "rbtree_node.h"
#include "rbtree.h"
#include "rbtree.hpp"
#include "rbtree_iterator.h"

template <typename T>
using OrderedSet = ExtendedSetI<T, RBTree<T>, RBTreeIterator<T>>;

#endif //LAB2_MY_SET_H
