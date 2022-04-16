#include "rbtree_iterator.h"


template<typename T>
T *RBTree<T>::RBTreeIterator::operator->()
{
	return &(this->node_ptr.lock()->data);
}

template<typename T>
typename RBTree<T>::RBTreeIterator RBTree<T>::RBTreeIterator::next()
{
	NodePtr<T> p;
	NodePtr<T> tnull = tree->tnull;

	if (node_ptr.lock() == tnull)
	{
		// ++ from end(). get the root of the tree
		node_ptr = tree->root;

		// error! ++ requested for an empty tree
		if (node_ptr.lock() == tnull)
			throw std::invalid_argument("++ requested for empty tree");

		// move to the smallest value in the tree,
		// which is the first node inorder
		while (node_ptr.lock()->left != tnull) {
			node_ptr = node_ptr.lock()->left;
		}
	}
	else
	if (node_ptr.lock()->right != tnull)
	{
		// successor is the farthest left node of
		// right subtree
		node_ptr = node_ptr.lock()->right;

		while (node_ptr.lock()->left != tnull) {
			node_ptr = node_ptr.lock()->left;
		}
	}
	else
	{
		// have already processed the left subtree, and
		// there is no right subtree. move up the tree,
		// looking for a parent for which node_ptr is a left child,
		// stopping if the parent becomes NULL. a non-NULL parent
		// is the successor. if parent is NULL, the original node
		// was the last node inorder, and its successor
		// is the end of the list
		p = node_ptr.lock()->parent;
		while (p != nullptr && node_ptr.lock() == p->right)
		{
			node_ptr = p;
			p = p->parent;
		}

		// if we were previously at the right-most node in
		// the tree, node_ptr = nullptr, and the iterator specifies
		// the end of the list
		node_ptr = p;
	}

	return *this;
}

template<typename T>
T &RBTree<T>::RBTreeIterator::operator*()
{
	return this->node_ptr.lock()->data;
}

template<typename T>
T RBTree<T>::RBTreeIterator::get() const
{
	return node_ptr.lock()->data;
}

template<typename T>
typename RBTree<T>::RBTreeIterator RBTree<T>::RBTreeIterator::operator++(int)
{
	return next();
}

template<typename T>
typename RBTree<T>::RBTreeIterator &RBTree<T>::RBTreeIterator::operator++()
{
	return next();
}


template<typename T>
bool RBTree<T>::RBTreeIterator::operator==(const RBTree<T>::RBTreeIterator &other)
{
	return this->get() == other.get();
}

template<typename T>
bool RBTree<T>::RBTreeIterator::operator!=(const RBTree<T>::RBTreeIterator &other)
{
	return this->get() != other.get();
}

template<typename T>
typename RBTree<T>::RBTreeIterator RBTree<T>::begin() const
{
	return RBTree<T>::RBTreeIterator(minimum(root), this);
}

template<typename T>
typename RBTree<T>::RBTreeIterator RBTree<T>::end() const
{
	return RBTree<T>::RBTreeIterator(maximum(root), this);
}


template<typename T>
void RBTree<T>::RBTreeIterator::skip()
{
	next();
}

template<typename T>
RBTree<T>::RBTreeIterator::operator bool() const
{
	return *this != this->tree->end();
}
