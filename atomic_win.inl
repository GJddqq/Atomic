#pragma execution_character_set("utf-8")
#include <Windows.h>
#include "atomic.h"

//重载前置++
template<typename T>
T Atomic<T>::operator++()
{
    return InterlockedIncrement(&m_value);
}

//重载后置++
template<typename T>
T Atomic<T>::operator++(int)
{
    return InterlockedIncrement(&m_value) - 1;
}

//重载前置--
template<typename T>
T Atomic<T>::operator--()
{
    return InterlockedDecrement(&m_value);
}

//重载后置--
template<typename T>
T Atomic<T>::operator--(int)
{
    return InterlockedDecrement(&m_value) + 1;
}

//重载加法运算符
template<typename T>
T Atomic<T>::operator+=(T value)
{
    return InterlockedExchangeAdd(&m_value, value) + value;
}

//重载减法运算符
template<typename T>
T Atomic<T>::operator-=(T value)
{
    return InterlockedExchangeAdd(&m_value, -value) - value;
}

//重载赋值运算符
template<typename T>
T Atomic<T>::operator=(T value)
{
    InterlockedExchange(&m_value, value);
    return value;
}

template<typename T>
T Atomic<T>::getValue() const
{
    return m_value;
}

