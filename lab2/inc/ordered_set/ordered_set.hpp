//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ORDERED_SET_HPP
#define LAB2_ORDERED_SET_HPP

#include "ordered_set.h"
#include "errors.h"

template<typename T>
bool OrderedSet<T>::empty() const
{
	return capacity == 0;
}

template<typename T>
size_t OrderedSet<T>::size() const
{
	return capacity;
}

template<typename T>
bool OrderedSet<T>::insert(const T &elem)
{
	try
	{
		set.insert(elem);
		capacity += 1;
		return true;
	}
	catch (const AlreadyInSetError &e)
	{
		return false;
	}
}

template<typename T>
void OrderedSet<T>::remove(const T &elem)
{
	if (set.contains(elem))
	{
		set.remove(elem);
		capacity -= 1;
	}
	else
	{
		time_t t_time = time(NULL);
		throw NotInSetError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
	}
}

template<typename T>
void OrderedSet<T>::discard(const T &elem)
{
	if (set.contains(elem))
	{
		set.remove(elem);
		capacity -= 1;
	}
}

template<typename T>
bool OrderedSet<T>::contains(const T &elem) const
{
	return set.contains(elem);
}

template<typename T>
void OrderedSet<T>::clear()
{
	set.clear();
}

template<typename T>
RBTreeIterator<T> OrderedSet<T>::find(const T &elem) const
{
	return set.find(elem);
}

template<typename T>
RBTreeIterator<T> OrderedSet<T>::begin() const
{
	return set.begin();
}

template<typename T>
RBTreeIterator<T> OrderedSet<T>::end() const
{
	return set.end();
}

template<typename T>
OrderedSet<T> OrderedSet<T>::union_(const OrderedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		result.insert(elem);
	for (auto elem: other)
		result.insert(elem);
	return result;
}

template<typename T>
OrderedSet<T> OrderedSet<T>::difference(const OrderedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		if (not other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T>
OrderedSet<T> OrderedSet<T>::intersection(const OrderedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		if (other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T>
OrderedSet<T>
OrderedSet<T>::sym_difference(const OrderedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		if (not other.contains(elem))
			result.insert(elem);

	for (auto elem: other)
		if (not this->contains(elem))
			result.insert(elem);
	return result;
}

template<typename T>
bool OrderedSet<T>::is_subset(const OrderedSet::MyType &other) const
{
	for (auto elem: *this)
		if (not other.contains(elem))
			return false;
	return true;
}

template<typename T>
OrderedSet<T>::OrderedSet(const std::initializer_list<T> elems)
{
	for (auto elem: elems)
		this->insert(elem);
}

template<typename T>
OrderedSet<T>::OrderedSet(const OrderedSet::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}

template<typename T>
OrderedSet<T>::OrderedSet(const T *elem_list, size_t len)
{
	for (int i = 0; i < len; i++)
		this->insert(elem_list[i]);
}

template<typename T>
void OrderedSet<T>::update(const OrderedSet::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}

template<typename T>
OrderedSet<T> &OrderedSet<T>::operator=(const OrderedSet::MyType &other)
{
	set->clear();
	for (auto elem: other)
		this->insert(elem);
}

template<typename T>
OrderedSet<T> &OrderedSet<T>::operator=(const OrderedSet::MyType &&other)
 noexcept {
	set = std::unique_ptr(other.set);
}

template<typename T>
bool OrderedSet<T>::operator==(const OrderedSet::MyType &other) const
{
	return this->is_subset(other) and other.is_subset(*this);
}

template<typename T>
bool OrderedSet<T>::operator!=(const OrderedSet::MyType &other) const
{
	return not (*this == other);
}


template<typename T>
void OrderedSet<T>::operator&=(const OrderedSet::MyType &other)
{
	*this = this->intersection(other);
}

template<typename T>
void OrderedSet<T>::operator|=(const OrderedSet::MyType &other)
{
	*this = this->union_(other);
}

template<typename T>
void OrderedSet<T>::operator^=(const OrderedSet::MyType &other)
{
	*this = this->sym_difference(other);
}

template<typename T>
void OrderedSet<T>::operator-=(const OrderedSet::MyType &other)
{
	*this = this->difference(other);
}

template<typename T>
void OrderedSet<T>::operator&(const OrderedSet::MyType &other) const
{
	return this->intersection(other);
}

template<typename T>
void OrderedSet<T>::operator|(const OrderedSet::MyType &other) const
{
	return this->union_(other);
}

template<typename T>
void OrderedSet<T>::operator^(const OrderedSet::MyType &other) const
{
	return this->sym_difference(other);
}

template<typename T>
void OrderedSet<T>::operator-(const OrderedSet::MyType &other) const
{
	return this->difference(other);
}

template<typename T>
OrderedSet<T>::OrderedSet(OrderedSet::MyType &&other) noexcept
{
	this->set.move(other.set);
}


#endif //LAB2_ORDERED_SET_HPP
