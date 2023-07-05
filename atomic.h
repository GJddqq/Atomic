#ifndef ATOMIC_H_
#define ATOMIC_H_

template <typename T>
class Atomic
{
private:
    volatile T m_value;

public:
    Atomic(T value = 0) :m_value(value) {}

    //重载前置++
    T operator++();

    //重载后置++
    T operator++(int);

    //重载前置--
    T operator--();

    //重载后置--
    T operator--(int);

    //重载加法运算符
    T operator+=(T value);

    //重载减法运算符
    T operator-=(T value);

    //重载赋值运算符
    T operator=(T value);

    T getValue() const;
};

#define ATOMIC_INCREMENT(obj) (++obj)
#define ATOMIC_POST_INCREMENT(obj) (obj++)
#define ATOMIC_DECREMENT(obj) (--obj)
#define ATOMIC_POST_DECREMENT(obj) (obj--)
#define ATOMIC_ADD(obj, value) (obj += value)
#define ATOMIC_SUBTRACT(obj, value) (obj -= value)
#define ATOMIC_ASSIGN(obj, value) (obj = value)
#define ATOMIC_GET_VALUE(obj) (obj.getValue())

#ifdef _WIN32
#include "atomic_win.inl"
#else
#include "atomic_linux.inl"

#endif

#endif

