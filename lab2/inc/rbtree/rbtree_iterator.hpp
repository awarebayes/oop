#ifndef __RBTREE_ITERATOR_HPP__
#define __RBTREE_ITERATOR_HPP__

#include "rbtree_iterator.h"
#include "errors.h"


template<typename T>
T *RBTreeIterator<T>::operator->()
{
	return &(this->current_node.lock()->data);
}

template<typename T>
void RBTreeIterator<T>::back_to_parents()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent;
	while (parent != nullptr && shared_node_ptr == parent->right)
	{
		shared_node_ptr = parent;
		parent = parent->parent;
	}
	current_node = parent;
}

template<typename T>
void RBTreeIterator<T>::find_successor()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	shared_node_ptr = shared_node_ptr->right;
	while (shared_node_ptr->left != nullptr)
		shared_node_ptr = shared_node_ptr->left;
	current_node = shared_node_ptr;
}

void iteration_stopped()
{
	time_t t_time = time(nullptr);
	throw IterationStoppedError(__FILE__, "RBTreeIterator<T>", __LINE__, ctime(&t_time));
}

template<typename T>
const RBTreeIterator<T> RBTreeIterator<T>::next()
{
	NodePtr<T> shared_node_ptr = current_node.lock();

	if (shared_node_ptr == nullptr)
		iteration_stopped();
	else if (shared_node_ptr->right != nullptr)
		find_successor();
	else
		back_to_parents();
	return *this;
}

template<typename T>
T &RBTreeIterator<T>::operator*()
{
	return this->current_node.lock()->data;
}

template<typename T>
T RBTreeIterator<T>::get() const
{
	return current_node.lock()->data;
}

template<typename T>
const RBTreeIterator<T> RBTreeIterator<T>::operator++(int)
{
	return next();
}

template<typename T>
const RBTreeIterator<T> &RBTreeIterator<T>::operator++()
{
	return next();
}


template<typename T>
bool RBTreeIterator<T>::operator==(const RBTreeIterator &other)
{
	return this->get() == other.get();
}

template<typename T>
bool RBTreeIterator<T>::operator!=(const RBTreeIterator &other)
{
	auto this_shared_ptr = this->current_node.lock();
	auto other_shared_ptr = other.current_node.lock();
	if (not this_shared_ptr and not other_shared_ptr)
		return false;
	if (not other_shared_ptr)
		return true;
	return this_shared_ptr != other_shared_ptr;
}

template<typename T>
RBTreeIterator<T>::operator bool() const
{
	current_node.lock() == nullptr;
}

template<typename T>
RBTreeIterator<T>::RBTreeIterator(const NodePtr<T> node_ptr_)
{
	current_node = node_ptr_;
}



#endif
