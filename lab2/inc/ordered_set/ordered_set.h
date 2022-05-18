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

	explicit OrderedSet(std::initializer_list<T> elems);
	OrderedSet(const T *elem_list, size_t len);
	explicit OrderedSet(std::set<T> std_set);
	explicit OrderedSet(std::vector<T> std_vector);
	OrderedSet(typename std::set<T>::iterator begin, typename std::set<T>::iterator end);

	OrderedSet(const MyType &other);
	OrderedSet(MyType &&other) noexcept;

	[[nodiscard]] virtual bool empty() const;
	[[nodiscard]] virtual size_t size() const;

	virtual bool insert(const T &elem);
	MyType operator +(const T &elem) const;
	void operator +=(const T &elem);

	virtual void remove(const T &elem);
	virtual void discard(const T &elem);
	virtual bool contains(const T &elem) const;

	void clear();

	MyType intersection(const MyType &other) const;
	MyType operator &(const MyType &other) const;
	void operator &=(const MyType &other);

	MyType union_(const MyType &other) const;
	MyType operator |(const MyType &other) const;
	void operator |=(const MyType &other);
	void update(const MyType &other);

	MyType difference(const MyType &other) const ;
	MyType operator -(const MyType &other) const;
	void operator -=(const MyType &other);

	MyType sym_difference(const MyType &other) const;
	MyType operator ^(const MyType &other) const;
	void operator ^=(const MyType &other);

	bool is_subset(const MyType &other) const;

	RBTreeIterator<T> begin() const;
	RBTreeIterator<T> end() const;
	RBTreeIterator<T> find(const T &elem) const;

	MyType &operator=(const MyType &other); // copy
	MyType &operator=(const MyType &&other) noexcept; // move

	bool operator ==(const MyType &other) const;
	bool operator !=(const MyType &other) const;

private:
	size_t capacity = 0;
	RBTree<T> set = RBTree<T>();
};


#endif //LAB2_ORDERED_SET_H
