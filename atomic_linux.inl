#include <cstdlib>
#include "atomic.h"

template<typename T>
T Atomic<T>::operator++() {
    return __sync_add_and_fetch(&m_value, 1);
}

template<typename T>
T Atomic<T>::operator--() {
    return __sync_sub_and_fetch(&m_value, 1);
}

template<typename T>
T Atomic<T>::operator++(int) {
    return __sync_fetch_and_add(&m_value, 1); // 后缀++
}

template<typename T>
T Atomic<T>::operator--(int) {
    return __sync_fetch_and_sub(&m_value, 1); // 后缀--
}

template<typename T>
T Atomic<T>::operator+=(T addend) {
    return __sync_add_and_fetch(&m_value, addend);
}

template<typename T>
T Atomic<T>::operator-=(T subtrahend) {
    return __sync_sub_and_fetch(&m_value, subtrahend);
}

template<typename T>
T Atomic<T>::operator=(T newValue) {
    __sync_lock_test_and_set(&m_value, newValue);
    return newValue;
}

template<typename T>
T Atomic<T>::getValue() const {
    return __sync_fetch_and_add(const_cast<volatile T*>(&m_value), 0);
}

