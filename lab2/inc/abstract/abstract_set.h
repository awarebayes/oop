//
// Created by dev on 4/16/22.
//

#ifndef LAB2_ABSTRACT_SET_H
#define LAB2_ABSTRACT_SET_H

#include <memory>

template<typename T, typename IteratorType>
class BasicSetI
{
public:
	virtual void insert(T key) = 0;

	virtual void remove(T key) = 0;

	virtual bool contains(T key) const = 0;

	virtual void clear() = 0;

	virtual IteratorType find(T key) const = 0;

	virtual IteratorType begin() const = 0;

	virtual IteratorType end() const = 0;
};


template<typename T, typename SetType, typename IteratorType>
class ExtendedSet : public BasicSetI<T, IteratorType>
{
	using MyType = ExtendedSet<T, SetType, IteratorType>;
	using BaseInterface = BasicSetI<T, IteratorType>;
public:

	ExtendedSet() = default;
	~ExtendedSet() = default;

	ExtendedSet(const MyType &other);

	ExtendedSet(std::initializer_list<T> elems);

	ExtendedSet(const T *elem_list, size_t len);

	void update(const MyType &other);

	[[nodiscard]] virtual bool empty() const;

	[[nodiscard]] virtual size_t size() const;

	virtual void insert(T key);

	virtual void remove(T key);

	virtual void discard(T key);

	virtual bool contains(T key) const;

	virtual void clear();

	virtual ExtendedSet union_(const MyType &other) const;

	virtual ExtendedSet intersection(const MyType &other) const;

	virtual ExtendedSet difference(const MyType &other) const ;

	virtual ExtendedSet sym_difference(const MyType &other) const;

	virtual bool is_subset(const MyType &other) const;

	virtual IteratorType begin() const;

	virtual IteratorType end() const;

	virtual IteratorType find(T key) const;

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
	std::unique_ptr<BaseInterface> set = std::make_unique<SetType>();
};


#endif //LAB2_ABSTRACT_SET_H
