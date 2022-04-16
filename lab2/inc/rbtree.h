//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_H
#define LAB2_RBTREE_H

#include <memory>
#include "abstract_set.h"
#include "rbtree_iterator.h"

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
using NodePtr = std::shared_ptr<Node<T>>;

template<typename T>
class RBTree: public BasicSetI<T, RBTreeIterator<T>>
{
private:
	NodePtr<T> root;
	NodePtr<T> tnull;

	NodePtr<T> searchTreeHelper(NodePtr<T> node, T key);

	void fixDelete(NodePtr<T> x);

	void rbTransplant(NodePtr<T> u, NodePtr<T> v);

	void deleteNodeHelper(NodePtr<T> node, T key);

	void fixInsert(NodePtr<T> k);

	void printHelper(NodePtr<T> root, std::string indent, bool last);

	NodePtr<T> searchTree(T k);

	NodePtr<T> minimum(NodePtr<T> node) const;

	NodePtr<T> maximum(NodePtr<T> node) const;

	void leftRotate(NodePtr<T> x);

	void rightRotate(NodePtr<T> x);


public:
	RBTree();
	~RBTree();

	void insert(T key);

	void remove(T key);

	bool contains(T key);

	void clear();

	void prettyPrint();

	RBTreeIterator<T> begin() const;
	RBTreeIterator<T> end() const;
};



#endif //LAB2_RBTREE_H
