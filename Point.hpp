#pragma once
#include <cmath>

template <class T> struct Point {
    T x;
    T y;

    Point<T> operator+ (Point<T> p) const{
        return Point<T>{x + p.x, y + p.y};
    }

    Point operator- (Point<T> p) const{
        return Point<T>{x - p.x, y - p.y};
    }

    Point<T> operator* (Point<T> p) const{
        return Point<T>{x * p.x, y * p.y};
    }

    Point<T> operator/ (Point<T> p) const{
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

    bool operator< (const Point<T> p) const{
        if (x < p.x and y < p.y)
            return true;
        return false;
    }

    bool operator> (const Point<T> p) const{
        if (x > p.x and y > p.y)
            return true;
        return false;
    }

    bool operator<= (const Point<T> p) const{
        if (x <= p.x and y <= p.y)
            return true;
        return false;
    }

    bool operator>= (const Point<T> p) const{
        if (x >= p.x and y >= p.y)
            return true;
        return false;
    }

    [[nodiscard]] Point<size_t> toSize_t() const{
        return Point<size_t> {(size_t)x, (size_t)y};;
    }

    [[nodiscard]] Point<double> toDouble() const{
        return Point<double> {(double)x, (double)y};;
    }
};

template <typename T>
Point<T> floor(Point<T> p) {
    return Point<T> {std::floor(p.x), std::floor(p.y)};
}