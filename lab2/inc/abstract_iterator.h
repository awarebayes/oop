//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_ITERATOR_H
#define LAB2_ABSTRACT_ITERATOR_H

template <typename T>
class IteratorI
{
public:
	virtual T get() const = 0;
	virtual void skip() = 0;
	virtual operator bool() const = 0;
};

#endif //LAB2_ABSTRACT_ITERATOR_H
