//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_HPP
#define LAB2_ABSTRACT_SET_HPP

#include "abstract_set.h"
#include "errors.h"

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSet<T, SetType, IteratorType>::empty() const
{
	return capacity == 0;
}

template<typename T, typename SetType, typename IteratorType>
size_t ExtendedSet<T, SetType, IteratorType>::size() const
{
	return capacity;
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::insert(T key)
{
	try
	{
		set->insert(key);
		capacity += 1;
	}
	catch (const AlreadyInSetError &e)
	{
	}
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::remove(T key)
{
	if (set->contains(key))
	{
		set->remove(key);
		capacity -= 1;
	}
	else
	{
		time_t t_time = time(NULL);
		throw NotInSetError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
	}
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::discard(T key)
{
	if (set->contains(key))
	{
		set->remove(key);
		capacity -= 1;
	}
}

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSet<T, SetType, IteratorType>::contains(T key) const
{
	return set->contains(key);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::clear()
{
	set->clear();
}

template<typename T, typename SetType, typename IteratorType>
IteratorType ExtendedSet<T, SetType, IteratorType>::find(T key) const
{
	return set->find(key);
}

template<typename T, typename SetType, typename IteratorType>
IteratorType ExtendedSet<T, SetType, IteratorType>::begin() const
{
	return set->begin();
}

template<typename T, typename SetType, typename IteratorType>
IteratorType ExtendedSet<T, SetType, IteratorType>::end() const
{
	return set->end();
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType> ExtendedSet<T, SetType, IteratorType>::union_(const ExtendedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		result.insert(elem);
	for (auto elem: other)
		result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType> ExtendedSet<T, SetType, IteratorType>::difference(const ExtendedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		if (not other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType> ExtendedSet<T, SetType, IteratorType>::intersection(const ExtendedSet::MyType &other) const
{
	MyType result;
	for (auto elem: *this)
		if (other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType>
ExtendedSet<T, SetType, IteratorType>::sym_difference(const ExtendedSet::MyType &other) const
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

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSet<T, SetType, IteratorType>::is_subset(const ExtendedSet::MyType &other) const
{
	for (auto elem: *this)
		if (not other.contains(elem))
			return false;
	return true;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType>::ExtendedSet(const std::initializer_list<T> elems)
{
	for (auto elem: elems)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType>::ExtendedSet(const ExtendedSet::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType>::ExtendedSet(const T *elem_list, size_t len)
{
	for (int i = 0; i < len; i++)
		this->insert(elem_list[i]);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::update(const ExtendedSet::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType> &ExtendedSet<T, SetType, IteratorType>::operator=(const ExtendedSet::MyType &other)
{
	set->clear();
	for (auto elem: other)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSet<T, SetType, IteratorType> &ExtendedSet<T, SetType, IteratorType>::operator=(const ExtendedSet::MyType &&other)
 noexcept {
	set = std::unique_ptr(other.set);
}

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSet<T, SetType, IteratorType>::operator==(const ExtendedSet::MyType &other) const
{
	return this->is_subset(other) and other.is_subset(*this);
}

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSet<T, SetType, IteratorType>::operator!=(const ExtendedSet::MyType &other) const
{
	return not (*this == other);
}


template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator&=(const ExtendedSet::MyType &other)
{
	*this = this->intersection(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator|=(const ExtendedSet::MyType &other)
{
	*this = this->union_(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator^=(const ExtendedSet::MyType &other)
{
	*this = this->sym_difference(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator-=(const ExtendedSet::MyType &other)
{
	*this = this->difference(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator&(const ExtendedSet::MyType &other) const
{
	return this->intersection(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator|(const ExtendedSet::MyType &other) const
{
	return this->union_(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator^(const ExtendedSet::MyType &other) const
{
	return this->sym_difference(other);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSet<T, SetType, IteratorType>::operator-(const ExtendedSet::MyType &other) const
{
	return this->difference(other);
}


#endif //LAB2_ABSTRACT_SET_HPP
