//
// Created by dev on 3/5/22.
//

#include <inc/observable.h>


template<typename T>
void Observable<T>::notify() const
{
	for(const auto & listener: listeners)
		listener(*this);
}

template<typename T>
void Observable<T>::set_value(T val)
{
	this->value = val;
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

}

template<typename T>
T const &Observable<T>::get_value() const
{
	return value;
}


