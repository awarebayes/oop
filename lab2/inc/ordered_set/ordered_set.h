//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ORDERED_SET_H
#define LAB2_ORDERED_SET_H

#include <memory>
#include "rbtree/rbtree.h"
#include "rbtree/rbtree.hpp"
#include "basic_set.h"

template<typename T>
class OrderedSet
{
	using MyType = OrderedSet<T>;
public:

	OrderedSet() = default;
	~OrderedSet() = default;

	OrderedSet(const MyType &other);
	OrderedSet(MyType &&other) noexcept;

	OrderedSet(std::initializer_list<T> elems);

	OrderedSet(const T *elem_list, size_t len);

	void update(const MyType &other);

	[[nodiscard]] virtual bool empty() const;

	[[nodiscard]] virtual size_t size() const;

	virtual bool insert(const T &elem);
	virtual void remove(const T &elem);
	virtual void discard(const T &elem);
	virtual bool contains(const T &elem) const;

	void clear();

	virtual OrderedSet union_(const MyType &other) const;
	virtual OrderedSet intersection(const MyType &other) const;
	virtual OrderedSet difference(const MyType &other) const ;
	virtual OrderedSet sym_difference(const MyType &other) const;
	virtual bool is_subset(const MyType &other) const;

	virtual RBTreeIterator<T> begin() const;
	virtual RBTreeIterator<T> end() const;
	virtual RBTreeIterator<T> find(const T &elem) const;

	MyType &operator=(const MyType &other); // copy
	MyType &operator=(const MyType &&other) noexcept; // move

	bool operator ==(const MyType &other) const;
	bool operator !=(const MyType &other) const;

	void operator &(const MyType &other) const;
	void operator |(const MyType &other) const;
	void operator -(const MyType &other) const;
	void operator ^(const MyType &other) const;

	void operator |=(const MyType &other);
	void operator &=(const MyType &other);
	void operator -=(const MyType &other);
	void operator ^=(const MyType &other);

private:
	size_t capacity = 0;
	RBTree<T> set = RBTree<T>();
};


#endif //LAB2_ORDERED_SET_H
