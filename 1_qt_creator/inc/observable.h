//
// Created by dev on 3/5/22.
//

#ifndef INC_1_QT_CREATOR_OBSERVABLE_H
#define INC_1_QT_CREATOR_OBSERVABLE_H

#include <functional>
#include <list>

template<typename T>
using Listener = std::function<void(T const&)>;

template<typename T>
using Connection = typename std::list<Listener<T>>::iterator;

template<typename T>
struct Observable {
private:
	double value;
	std::list<Listener<T>> listeners;
	void notify() const;

public:
	T const &get_value() const;
	void set_value(T val);

	Connection<T> connect(Listener<T> l);
	void disconnect(Connection<T> c);
};



#endif //INC_1_QT_CREATOR_OBSERVABLE_H
