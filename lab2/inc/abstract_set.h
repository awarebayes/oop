//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_H
#define LAB2_ABSTRACT_SET_H
#include "abstract_iterator.h"

template <typename T, typename IteratorType>
class BasicSetI
{
	virtual void insert(T key) = 0;
	virtual void remove(T key) = 0;
	virtual bool contains(T key) = 0;
	virtual void clear() = 0;

	IteratorType begin() const = 0;
	IteratorType end() const = 0;
};

template <typename T, typename BaseSetType, typename IteratorType>
class ExtendedSetI
{
public:

	// explicit utility methods
	virtual bool empty() const;
	virtual size_t size() const;

	virtual void insert(T key);
	virtual void remove(T key);
	virtual void discard(T key);

	virtual ExtendedSetI union_(BasicSetI<T, IteratorType> other);

protected:
	BasicSetI<T, IteratorType> set = BaseSetType();
	size_t capacity = 0;
};



#endif //LAB2_ABSTRACT_SET_H
