//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <cassert>
#include <cmath>

template<class T>
union vec2 {
    struct {
        T x, y;
    };
    struct {
        T width, height;
    };

    float distance(const vec2 &other) const {
        return (float) sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
    }

    float norme() const {
        return (float) sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    vec2<T> normalize() const {
        assert(norme() != 0.f);
        return *this / norme();
    }
};

template<class T>
inline vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs) {
    vec2<T> nouveau{};
    nouveau.x = lhs.x + rhs.x;
    nouveau.y = lhs.y + rhs.y;

    return nouveau;
}

template<class T>
inline vec2<T> operator-(const vec2<T> &lhs, const vec2<T> &rhs) {
    return {{lhs.x - rhs.x, lhs.y - rhs.y}};
}

template<class T>
inline vec2<T> operator/(const vec2<T> &lhs, T rhs) {
    vec2<T> nouveau{};
    nouveau.x = lhs.x / rhs;
    nouveau.y = lhs.y / rhs;

    return nouveau;
}

template<class T>
inline vec2<T> operator*(const vec2<T> &lhs, T rhs) {
    vec2<T> nouveau{};
    nouveau.x = lhs.x * rhs;
    nouveau.y = lhs.y * rhs;

    return nouveau;
}

template<class T>
inline vec2<T> operator*(T lhs, const vec2<T> &rhs) {
    vec2<T> nouveau{};
    nouveau.x = lhs * rhs.x;
    nouveau.y = lhs * rhs.y;

    return nouveau;
}