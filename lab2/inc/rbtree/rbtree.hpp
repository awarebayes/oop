//
// Created by dev on 4/16/22.
//
#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include "rbtree.h"
#include "errors.h"

template<typename T>
RBTree<T>::RBTree()
{
	root = nullptr;
}

template<typename T>
NodePtr<T> RBTree<T>::minimum(NodePtr<T> node) const
{
	if (root == nullptr)
		return nullptr;
	while (node->left != nullptr)
		node = node->left;
	return node;
}

template<typename T>
NodePtr<T> RBTree<T>::maximum(NodePtr<T> node) const
{
	while (node->right != nullptr)
		node = node->right;
	return node;
}



template<typename T>
void RBTree<T>::remove(const T &key)
{
	NodePtr<T> node = deleteBST(root, key);
	fixDeleteRBTree(node);
}

template<typename T>
bool RBTree<T>::contains(const T &key) const
{
	NodePtr<T> searchResult = searchTree(key);
	return searchResult != nullptr;
}

template<typename T>
RBTree<T>::~RBTree()
{
	if (root)
		root->kill_children();
	root = nullptr;
}

template<typename T>
RBTreeIterator<T> RBTree<T>::begin() const
{
	return RBTreeIterator<T>(minimum(root));
}

template<typename T>
RBTreeIterator<T> RBTree<T>::end() const
{
	return RBTreeIterator<T>(nullptr);
}

template<typename T>
RBTreeIterator<T> RBTree<T>::find(const T &key) const
{

	auto search_result = searchTree(key);
	return RBTreeIterator<T>(search_result);
}

template<typename T>
int RBTree<T>::getColor(NodePtr<T> node) const
{
	if (node == nullptr)
		return BLACK;
	return node->color;
}

template<typename T>
void RBTree<T>::setColor(NodePtr<T> node, int color)
{
	if (node == nullptr)
		return;

	node->color = color;
}

template<typename T>
NodePtr<T> RBTree<T>::insertBST(NodePtr<T> start, NodePtr<T> ptr)
{
	if (start == nullptr)
		return ptr;

	if (ptr->data < start->data) {
		start->left = insertBST(start->left, ptr);
		start->left->parent = start;
	} else if (ptr->data > start->data) {
		start->right = insertBST(start->right, ptr);
		start->right->parent = start;
	} else
	{
		time_t t_time = time(nullptr);
		throw AlreadyInSetError(__FILE__, "RBTreeIterator<T>", __LINE__, ctime(&t_time));
	}

	return start;
}

template<typename T>
void RBTree<T>::insert(const T &key)
{
	NodePtr<T> node = std::make_shared<Node<T>>(key);
	root = insertBST(root, node);
	fixInsertRBTree(node);
}

template<typename T>
void RBTree<T>::rotateLeft(NodePtr<T> ptr)
{
	NodePtr<T> right_child = ptr->right;
	ptr->right = right_child->left;

	if (ptr->right != nullptr)
		ptr->right->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = right_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = right_child;
	else
		ptr->parent->right = right_child;

	right_child->left = ptr;
	ptr->parent = right_child;
}

template<typename T>
void RBTree<T>::rotateRight(NodePtr<T> ptr)
{
	NodePtr<T> left_child = ptr->left;
	ptr->left = left_child->right;

	if (ptr->left != nullptr)
		ptr->left->parent = ptr;

	left_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = left_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = left_child;
	else
		ptr->parent->right = left_child;

	left_child->right = ptr;
	ptr->parent = left_child;
}

template<typename T>
void RBTree<T>::fixInsertRBTree(NodePtr<T> ptr)
{
	NodePtr<T> parent = nullptr;
	NodePtr<T> grandparent = nullptr;
	while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		parent = ptr->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			NodePtr<T> uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			} else {
				if (ptr == parent->right) {
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		} else {
			NodePtr<T> uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			} else {
				if (ptr == parent->left) {
					rotateRight(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
	}
	setColor(root, BLACK);
}

template<typename T>
void RBTree<T>::fixDeleteRBTree(NodePtr<T> node)
{
	if (node == nullptr)
		return;

	if (node == root) {
		root = nullptr;
		return;
	}

	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		NodePtr<T> child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
		} else {
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
		}
	} else {
		NodePtr<T>sibling = nullptr;
		NodePtr<T>parent = nullptr;
		NodePtr<T>ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
			parent = ptr->parent;
			if (ptr == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				} else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if(getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					} else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			} else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				} else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					} else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		setColor(root, BLACK);
	}
}

template<typename T>
NodePtr<T> RBTree<T>::deleteBST(NodePtr<T> start, const T &data)
{
	if (start == nullptr)
		return start;

	if (data < start->data)
		return deleteBST(start->left, data);

	if (data > start->data)
		return deleteBST(start->right, data);

	if (start->left == nullptr || start->right == nullptr)
		return start;

	NodePtr<T> temp = minimum(start->right);
	start->data = temp->data;
	return deleteBST(start->right, temp->data);
}

template<typename T>
int RBTree<T>::getBlackHeight(NodePtr<T> node)
{
	int blackheight = 0;
	while (node != nullptr) {
		if (getColor(node) == BLACK)
			blackheight++;
		node = node->left;
	}
	return blackheight;
}

template<typename T>
NodePtr<T> RBTree<T>::searchRBT(NodePtr<T> node, const T &value) const
{
	if (node == nullptr or node->data == value)
		return node;
	if (node->data > value)
		return searchRBT(node->left, value);
	return searchRBT(node->right, value);
}

template<typename T>
NodePtr<T> RBTree<T>::searchTree(const T &key) const
{
	return searchRBT(root, key);
}

template<typename T>
void RBTree<T>::clear()
{
	root->kill_children();
	root = nullptr;
}

template<typename T>
void RBTree<T>::move(RBTree<T> &other)
{
	this->root = other.root;
	other.root = nullptr;
}

#endif