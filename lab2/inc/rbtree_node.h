//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_NODE_H
#define LAB2_RBTREE_NODE_H

#include <memory>

template<typename T>
struct Node
{
	T data;
	std::shared_ptr<Node<T>> parent;
	std::shared_ptr<Node<T>> left;
	std::shared_ptr<Node<T>> right;
	int color = 0; // 1 -> Red, 0 -> Black

	Node() = default;
	explicit Node(T data) : data(data) {};
	explicit Node(std::shared_ptr<Node<T>> parent_) : parent(parent_) {};
	explicit Node(T data_, std::shared_ptr<Node<T>> parent_) : data(data_), parent(parent_) {};

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
