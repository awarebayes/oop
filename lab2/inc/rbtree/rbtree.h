//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_H
#define LAB2_RBTREE_H

#include <memory>
#include <basic_set.h>
#include "rbtree_node.h"
#include "rbtree_iterator.h"
#include "rbtree_iterator.hpp"

template<typename T>
class RBTree : public BasicSetI
{
	friend class RBTreeIterator<T>;

private:
	NodePtr<T> root;
	NodePtr<T> tnull;

	NodePtr<T> searchTreeHelper(NodePtr<T> node, T key) const;

	void fixDelete(NodePtr<T> x);

	void rbTransplant(NodePtr<T> u, NodePtr<T> v);

	void deleteNodeHelper(NodePtr<T> node, T key);

	void fixInsert(NodePtr<T> k);

	NodePtr<T> searchTree(T k) const;

	NodePtr<T> minimum(NodePtr<T> node) const;

	NodePtr<T> maximum(NodePtr<T> node) const;

	void leftRotate(NodePtr<T> x);

	void rightRotate(NodePtr<T> x);

public:
	RBTree();

	~RBTree();

	void insert(T key);

	void remove(T key);

	bool contains(T key) const;

	void clear();

	RBTreeIterator<T> find(T key) const;

	RBTreeIterator<T> begin() const;

	RBTreeIterator<T> end() const;
};


#endif //LAB2_RBTREE_H
