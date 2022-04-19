//
// Created by dev on 4/16/22.
//
#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include "rbtree.h"
#include "errors.h"


template<typename T>
NodePtr<T> RBTree<T>::searchTreeHelper(NodePtr<T> node, T key) const
{
	if (node == tnull || key == node->data)
		return node;
	if (key < node->data)
		return searchTreeHelper(node->left, key);
	return searchTreeHelper(node->right, key);
}

template<typename T>
void RBTree<T>::fixDelete(NodePtr<T> x)
{
	NodePtr<T> s;
	while (x != root && x->is_red == 0)
	{
		if (x == x->parent->left)
		{
			s = x->parent->right;
			if (s->is_red == 1)
			{
				// case 3.1
				s->is_red = 0;
				x->parent->is_red = 1;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->is_red == 0 && s->right->is_red == 0)
			{
				// case 3.2
				s->is_red = 1;
				x = x->parent;
			}
			else
			{
				if (s->right->is_red == 0)
				{
					// case 3.3
					s->left->is_red = 0;
					s->is_red = 1;
					rightRotate(s);
					s = x->parent->right;
				}

				// case 3.4
				s->is_red = x->parent->is_red;
				x->parent->is_red = 0;
				s->right->is_red = 0;
				leftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			s = x->parent->left;
			if (s->is_red == 1)
			{
				// case 3.1
				s->is_red = 0;
				x->parent->is_red = 1;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->left->is_red == 0 && s->right->is_red == 0)
			{
				// case 3.2
				s->is_red = 1;
				x = x->parent;
			}
			else
			{
				if (s->left->is_red == 0)
				{
					// case 3.3
					s->right->is_red = 0;
					s->is_red = 1;
					leftRotate(s);
					s = x->parent->left;
				}

				// case 3.4
				s->is_red = x->parent->is_red;
				x->parent->is_red = 0;
				s->left->is_red = 0;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->is_red = 0;
}

template<typename T>
void RBTree<T>::rbTransplant(NodePtr<T> u, NodePtr<T> v)
{
	if (u->parent == nullptr)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

template<typename T>
void RBTree<T>::deleteNodeHelper(NodePtr<T> node, T key)
{
	NodePtr<T> z = tnull;
	NodePtr<T> x, y;
	while (node != tnull)
	{
		if (node->data == key)
		{
			z = node;
		}

		if (node->data <= key)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}

	if (z == tnull)
	{
		time_t t_time = time(NULL);
		throw NotInSetError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
	}

	y = z;
	int y_original_color = y->is_red;
	if (z->left == tnull)
	{
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == tnull)
	{
		x = z->left;
		rbTransplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->is_red;
		x = y->right;
		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->is_red = z->is_red;
	}
	if (y_original_color == 0)
	{
		fixDelete(x);
	}
}

template<typename T>
void RBTree<T>::fixInsert(NodePtr<T> k)
{
	NodePtr<T> u;
	while (k->parent->is_red == 1)
	{
		if (k->parent == k->parent->parent->right)
		{
			u = k->parent->parent->left; // uncle
			if (u->is_red == 1)
			{
				// case 3.1
				u->is_red = 0;
				k->parent->is_red = 0;
				k->parent->parent->is_red = 1;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->left)
				{
					// case 3.2.2
					k = k->parent;
					rightRotate(k);
				}
				// case 3.2.1
				k->parent->is_red = 0;
				k->parent->parent->is_red = 1;
				leftRotate(k->parent->parent);
			}
		}
		else
		{
			u = k->parent->parent->right; // uncle

			if (u->is_red == 1)
			{
				// mirror case 3.1
				u->is_red = 0;
				k->parent->is_red = 0;
				k->parent->parent->is_red = 1;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->right)
				{
					// mirror case 3.2.2
					k = k->parent;
					leftRotate(k);
				}
				// mirror case 3.2.1
				k->parent->is_red = 0;
				k->parent->parent->is_red = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root)
		{
			break;
		}
	}
	root->is_red = 0;
}


template<typename T>
RBTree<T>::RBTree()
{
	tnull = std::make_shared<Node<T>>();
	root = tnull;
}


template<typename T>
NodePtr<T> RBTree<T>::searchTree(T k) const
{
	return searchTreeHelper(root, k);
}

template<typename T>
NodePtr<T> RBTree<T>::minimum(NodePtr<T> node) const
{
	if (root == tnull)
		return tnull;
	while (node->left != tnull)
	{
		node = node->left;
	}
	return node;
}

template<typename T>
NodePtr<T> RBTree<T>::maximum(NodePtr<T> node) const
{
	while (node->right != tnull)
	{
		node = node->right;
	}
	return node;
}

template<typename T>
void RBTree<T>::leftRotate(NodePtr<T> x)
{
	NodePtr<T> y = x->right;
	x->right = y->left;
	if (y->left != tnull)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		this->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template<typename T>
void RBTree<T>::rightRotate(NodePtr<T> x)
{
	NodePtr<T> y = x->left;
	x->left = y->right;
	if (y->right != tnull)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		this->root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

template<typename T>
void RBTree<T>::insert(T key)
{
	// Ordinary Binary Search Insertion
	NodePtr<T> node = std::make_shared<Node<T>>();
	node->data = key;
	node->left = tnull;
	node->right = tnull;
	node->is_red = 1; // new node must be red

	NodePtr<T> y = nullptr;
	NodePtr<T> x = this->root;

	while (x != tnull)
	{
		y = x;
		if (node->data < x->data)
		{
			x = x->left;
		}
		else if (node->data > x->data)
		{
			x = x->right;
		}
		else
		{
			time_t t_time = time(NULL);
			throw AlreadyInSetError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
		}
	}

	// y is parent of x
	node->parent = y;
	if (y == nullptr)
	{
		root = node;
	}
	else if (node->data < y->data)
	{
		y->left = node;
	}
	else
	{
		y->right = node;
	}

	// if new node is a root node, simply return
	if (node->parent == nullptr)
	{
		node->is_red = 0;
		return;
	}

	// if the grandparent is null, simply return
	if (node->parent->parent == nullptr)
	{
		return;
	}

	// Fix the tree
	fixInsert(node);
}

template<typename T>
void RBTree<T>::remove(T key)
{
	deleteNodeHelper(this->root, key);
}

template<typename T>
bool RBTree<T>::contains(T key) const
{
	NodePtr<T> searchResult = searchTree(key);
	return searchResult != tnull;
}


template<typename T>
void RBTree<T>::clear()
{
	root->kill_children();
	root = tnull;
}

template<typename T>
RBTree<T>::~RBTree()
{
	clear();
	tnull = nullptr;
	root = nullptr;
}

template<typename T>
RBTreeIterator<T> RBTree<T>::begin() const
{
	return RBTreeIterator<T>(minimum(root), *this);
}

template<typename T>
RBTreeIterator<T> RBTree<T>::end() const
{
	return RBTreeIterator<T>(tnull, *this);
}

template<typename T>
RBTreeIterator<T> RBTree<T>::find(T key) const
{

	auto search_result = searchTree(key);
	return RBTreeIterator<T>(search_result, *this);
}

#endif
