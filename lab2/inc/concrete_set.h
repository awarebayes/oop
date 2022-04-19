//
// Created by dev on 4/16/22.
//

#ifndef LAB2_CONCRETE_SET_H
#define LAB2_CONCRETE_SET_H

#include "abstract/abstract_set.h"
#include "abstract/abstract_set.hpp"
#include "rbtree/rbtree_node.h"
#include "rbtree/rbtree.h"
#include "rbtree/rbtree.hpp"
#include "rbtree/rbtree_iterator.h"

template<typename T>
using OrderedSet = ExtendedSet<T, RBTree<T>, RBTreeIterator<T>>;

#endif //LAB2_CONCRETE_SET_H
