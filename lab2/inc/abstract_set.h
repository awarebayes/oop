//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_H
#define LAB2_ABSTRACT_SET_H

#include <memory>

template <typename T, typename IteratorType>
class BasicSetI
{
public:
	virtual void insert(T key) = 0;
	virtual void remove(T key) = 0;
	virtual bool contains(T key) const = 0;
	virtual void clear() = 0;

	virtual IteratorType begin() const = 0;
	virtual IteratorType end() const = 0;
};

template <typename T, typename SetType, typename IteratorType>
class ExtendedSetI : public BasicSetI<T, IteratorType>
{
	using MyType = ExtendedSetI<T, SetType, IteratorType>;
	using BaseInterface = BasicSetI<T, IteratorType>;
public:

	ExtendedSetI() = default;
	ExtendedSetI(const MyType &other);
	ExtendedSetI(const std::initializer_list<T> elems);
	ExtendedSetI(const T *elem_list, size_t len);
	~ExtendedSetI() = default;

	void update(const MyType &other);

	// explicit utility methods
	virtual bool empty() const;
	virtual size_t size() const;

	virtual void insert(T key);
	virtual void remove(T key);
	virtual void discard(T key);
	virtual bool contains(T key) const;
	virtual void clear();

	virtual ExtendedSetI union_(MyType &other);
	virtual ExtendedSetI intersection(MyType &other);
	virtual ExtendedSetI difference(MyType &other);
	virtual ExtendedSetI sym_difference(MyType &other);

	virtual bool is_subset(MyType &other) const;

	virtual IteratorType begin() const;
	virtual IteratorType end() const;

	std::unique_ptr<BaseInterface> set = std::make_unique<SetType>();

protected:
	size_t capacity = 0;
};


#endif //LAB2_ABSTRACT_SET_H
