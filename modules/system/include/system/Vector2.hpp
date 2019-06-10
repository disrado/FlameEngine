#pragma once

namespace flm
{

template<typename T>
class Vector2 {
public:
    Vector2() = default;
    Vector2(T x, T y);

    template<typename U>
    Vector2(const Vector2<U>& vector);

public:
    T x = 0; 
    T y = 0;
};

template<typename T>
Vector2<T> operator -(const Vector2<T>& right);

template<typename T>
const Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

template<typename T>
const Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

template<typename T>
Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

template<typename T>
const Vector2<T> operator *(const Vector2<T>& left, T right);

template<typename T>
const Vector2<T> operator *(T left, const Vector2<T>& right);

template<typename T>
Vector2<T>& operator *=(Vector2<T>& left, T right);

template<typename T>
const Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
const Vector2<T> operator /(const Vector2<T>& left, T right);

template<typename T>
Vector2<T>& operator /=(Vector2<T>& left, T right);

template <typename T>
bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
bool operator !=(const Vector2<T>& left, const Vector2<T>& right);


#include <system/Vector2.inl>

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;


} // flm