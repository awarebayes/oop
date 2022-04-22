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

protected:
	void rotateLeft(NodePtr<T> node);
	void rotateRight(NodePtr<T> node);
	void fixInsertRBTree(NodePtr<T> node);
	void fixDeleteRBTree(NodePtr<T> node);
	NodePtr<T> searchRBT(NodePtr<T> node, T value) const;
	int getColor(NodePtr<T> node) const;
	void setColor(NodePtr<T> node, int color);
	NodePtr<T> insertBST(NodePtr<T> node, NodePtr<T> ptr);
	NodePtr<T> deleteBST(NodePtr<T> node, T key);
	NodePtr<T> minimum(NodePtr<T> node) const;
	NodePtr<T> maximum(NodePtr<T> node) const;
	NodePtr<T> searchTree(T key) const;
	int getBlackHeight(NodePtr<T>);
	
public:
	RBTree();

	~RBTree() override;

	void insert(T key);

	void remove(T key);

	void clear();

	bool contains(T key) const;

	RBTreeIterator<T> find(T key) const;

	RBTreeIterator<T> begin() const;

	RBTreeIterator<T> end() const;

};


#endif //LAB2_RBTREE_H
