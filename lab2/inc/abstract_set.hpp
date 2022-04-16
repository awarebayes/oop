//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_HPP
#define LAB2_ABSTRACT_SET_HPP

#include "abstract_set.h"

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
bool ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::empty() const
{
	return capacity() == 0;
}

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
size_t ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::size() const
{
	return capacity();
}

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
void ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::insert(T key)
{
	set.insert(key);
}

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
void ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::remove(T key)
{
	if (set.contains(key))
		set.remove(key);
	else
		throw std::runtime_error("Element was not in set");
}

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
void ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::discard(T key)
{
	if (set.contains(key))
		set.remove(key);
}

template<typename T, typename BaseSetClass, typename BaseIteratorClass>
ExtendedSetI ExtendedSetI<T, BaseSetClass, BaseIteratorClass>::union_(BasicSetI<T> other)
{
}


#endif //LAB2_ABSTRACT_SET_HPP
