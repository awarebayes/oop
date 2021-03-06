//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_NODE_H
#define LAB2_RBTREE_NODE_H

#include <memory>

enum NodeColor {RED, BLACK, DOUBLE_BLACK};

template<typename T>
struct Node
{
	T data;
	std::shared_ptr<Node<T>> parent;
	std::shared_ptr<Node<T>> left;
	std::shared_ptr<Node<T>> right;
	int color = RED;

	Node() = default;
	explicit Node(T value) : data(value) {};
	void kill_children();
};

template<typename T>
void Node<T>::kill_children()
{
	if (left)
		left->kill_children();
	if (right)
		right->kill_children();
	left = nullptr;
	right = nullptr;
}


template<typename T>
using NodePtr = std::shared_ptr<Node<T>>;

#endif //LAB2_RBTREE_NODE_H
