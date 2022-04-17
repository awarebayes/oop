//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_HPP
#define LAB2_ABSTRACT_SET_HPP

#include "abstract_set.h"
#include "errors.h"

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSetI<T, SetType, IteratorType>::empty() const
{
	return capacity == 0;
}

template<typename T, typename SetType, typename IteratorType>
size_t ExtendedSetI<T, SetType, IteratorType>::size() const
{
	return capacity;
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSetI<T, SetType, IteratorType>::insert(T key)
{
	try
	{
		set->insert(key);
		capacity += 1;
	}
	catch (const AlreadyInSetError& e)
	{}
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSetI<T, SetType, IteratorType>::remove(T key)
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
void ExtendedSetI<T, SetType, IteratorType>::discard(T key)
{
	if (set->contains(key))
	{
		set->remove(key);
		capacity -= 1;
	}
}

template<typename T, typename SetType, typename IteratorType>
IteratorType ExtendedSetI<T, SetType, IteratorType>::begin() const
{
	return set->begin();
}

template<typename T, typename SetType, typename IteratorType>
IteratorType ExtendedSetI<T, SetType, IteratorType>::end() const
{
	return set->end();
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType> ExtendedSetI<T, SetType, IteratorType>::union_(ExtendedSetI::MyType &other)
{
	MyType result;
	for (auto elem: *set)
		result.insert(elem);
	for (auto elem: other)
		result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType> ExtendedSetI<T, SetType, IteratorType>::difference(ExtendedSetI::MyType &other)
{
	MyType result;
	for (auto elem: *set)
		if (not other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSetI<T, SetType, IteratorType>::contains(T key) const
{
	return set->contains(key);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSetI<T, SetType, IteratorType>::clear()
{
	set->clear();
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType> ExtendedSetI<T, SetType, IteratorType>::intersection(ExtendedSetI::MyType &other)
{
	MyType result;
	for (auto elem: *set)
		if (other.contains(elem))
			result.insert(elem);
	return result;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType> ExtendedSetI<T, SetType, IteratorType>::sym_difference(ExtendedSetI::MyType &other)
{
	MyType result;
	for (auto elem: *set)
		if (not other.contains(elem))
			result.insert(elem);

	for (auto elem: *set)
		if (not this->contains(elem))
			result.insert(elem);

	return result;
}

template<typename T, typename SetType, typename IteratorType>
bool ExtendedSetI<T, SetType, IteratorType>::is_subset(ExtendedSetI::MyType &other) const
{
	for (auto elem: *set)
		if (not other.contains(elem))
			return false;
	return true;
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType>::ExtendedSetI(const std::initializer_list<T> elems)
{
	for (auto elem: elems)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType>::ExtendedSetI(const ExtendedSetI::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}

template<typename T, typename SetType, typename IteratorType>
ExtendedSetI<T, SetType, IteratorType>::ExtendedSetI(const T *elem_list, size_t len)
{
	for (int i = 0; i < len; i++)
		this->insert(elem_list[i]);
}

template<typename T, typename SetType, typename IteratorType>
void ExtendedSetI<T, SetType, IteratorType>::update(const ExtendedSetI::MyType &other)
{
	for (auto elem: other)
		this->insert(elem);
}


#endif //LAB2_ABSTRACT_SET_HPP
