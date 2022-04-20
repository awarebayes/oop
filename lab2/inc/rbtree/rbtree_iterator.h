//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_ITERATOR_H
#define LAB2_RBTREE_ITERATOR_H

#include "rbtree_node.h"

template<typename T>
class RBTree;

template<typename T>
class RBTreeIterator : public std::iterator<std::forward_iterator_tag, T>
{
	friend class RBTree<T>;

public:
	T &operator*();

	T *operator->();

	const RBTreeIterator next();

	T get() const;

	const RBTreeIterator<T> operator++(int);

	const RBTreeIterator<T> &operator++();

	bool operator==(const RBTreeIterator &other);

	bool operator!=(const RBTreeIterator &other);

	operator bool() const;


private:
	std::weak_ptr<Node<T>> current_node;
	std::weak_ptr<Node<T>> tnull_ptr;

	void back_to_parents();
	void find_successor();

	RBTreeIterator(const NodePtr<T> node_ptr_, const RBTree<T> &tree_);
};


#endif //LAB2_RBTREE_ITERATOR_H
