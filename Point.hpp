#pragma once
#include <cmath>

template <class T> struct Point {
    T x;
    T y;

    Point<T> operator+ (const Point<T>& p) const{
        return Point<T>{x + p.x, y + p.y};
    }

    Point<T> operator- (const Point<T>& p) const{
        return Point<T>{x - p.x, y - p.y};
    }

    Point<T> operator* (const Point<T>& p) const{
        return Point<T>{x * p.x, y * p.y};
    }

    Point<T> operator/ (const Point<T>& p) const{
        return Point<T>{x / p.x, y / p.y};
    }

    Point<T> operator+ (const T& value) const{
        return Point<T>{x + value, y + value};
    }

    Point<T> operator- (const T& value) const{
        return Point<T>{x - value, y - value};
    }

    Point<T> operator* (const T& value) const{
        return Point<T>{x * value, y * value};
    }

    Point<T> operator/ (const T& value) const{
        return Point<T>{x / value, y / value};
    }

    void operator+= (const Point<T>& p) {
        *this = *this + p;
    }

    void operator-= (const Point<T>& p) {
        *this = *this - p;
    }

    void operator*= (const Point<T>& p) {
        *this = *this * p;
    }

    void operator/= (const Point<T>& p) {
        *this = *this / p;
    }

    void operator+= (const T& value) {
        *this = *this + value;
    }

    void operator-= (const T& value) {
        *this = *this - value;
    }

    void operator*= (const T& value) {
        *this = *this * value;
    }

    void operator/= (const T& value) {
        *this = *this / value;
    }

    bool operator== (const Point<T>& p) const{
        if (x == p.x and y == p.y)
            return true;
        return false;
    }

    bool operator!= (const Point<T>& p) const{
        if (!(*this == p))
            return true;
        return false;
    }

    bool operator< (const Point<T>& p) const{
        if (x < p.x and y < p.y)
            return true;
        return false;
    }

    bool operator<= (const Point<T>& p) const{
        if (*this < p or *this == p)
            return true;
        return false;
    }

    bool operator> (const Point<T>& p) const{
        if (!(*this <= p))
            return true;
        return false;
    }

    bool operator>= (const Point<T>& p) const{
        if (*this > p or *this == p )
            return true;
        return false;
    }

    template <typename newT>
    Point<newT> convert (){
        return Point<newT>{(newT)x, (newT) y};
    }
};

template <typename T>
Point<T> floor(Point<T> p) {
    return Point<T> {std::floor(p.x), std::floor(p.y)};
}