//
// Created by dev on 3/5/22.
//

#ifndef INC_1_QT_CREATOR_OBSERVABLE_H
#define INC_1_QT_CREATOR_OBSERVABLE_H

#include <functional>
#include <list>

template<typename T>
using Listener = std::function<void(T const &)>;

template<typename T>
using Connection = typename std::list<Listener<T>>::iterator;

template<typename T>
struct Observable
{
private:
	T value;
	std::list<Listener<T>> listeners;

	void notify() const;

public:
	T const &get_value() const;

	void set_value(T val);

	Connection<T> connect(Listener<T> l);

	void disconnect(Connection<T> c);
};

template<typename T>
void Observable<T>::notify() const
{
	for (const auto &listener: listeners)
		listener(value);
}

template<typename T>
void Observable<T>::set_value(T val)
{
	this->value = val;
	notify();
}

template<typename T>
T const &Observable<T>::get_value() const
{
	return value;
}


template<typename T>
Connection<T> Observable<T>::connect(Listener<T> l)
{
	// Insert возвращает итератор
	return listeners.insert(listeners.end(), l);
}

template<typename T>
void Observable<T>::disconnect(Connection<T> c)
{
	// TODO
}

#endif //INC_1_QT_CREATOR_OBSERVABLE_H
