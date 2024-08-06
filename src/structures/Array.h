#pragma once
#include <array>
#include <iostream>

namespace Structures {
    template<typename T>
    class Point;

    template<typename T, int N>
    class Array {
    private:
        std::array<T, N> data;
    public:
        Array() {
            for (int i = 0; i < N; i++) {
                data[i] = 0;
            }
        }
        Array(const std::array<T, N>& data) : data(data) {}
        Array(const Structures::Point<T>& point) {
            static_assert(N == 2, "This constructor is only valid for arrays of size 2.");
            (*this)[0] = point.x;
            (*this)[1] = point.y;
        }
        bool operator==(const Array<T, N>& other) const {
            for (int i = 0; i < N; i++) {
                if (data[i] != other.data[i]) {
                    return false;
                }
            }
            return true;
        }
        T operator[](int index) const {
            return data.at(index);
        }
        T& operator[](int index) {
            return data.at(index);
        }
        Array operator+=(const Array<T, N>& other) {
            for (int i = 0; i < N; i++) {
                data[i] += other.data[i];
            }
            return *this;
        }
        Array operator-=(const Array<T, N>& other) {
            for (int i = 0; i < N; i++) {
                data[i] -= other.data[i];
            }
            return *this;
        }
        Array operator +(const Array<T, N>& other) const {
            Array result;
            for (int i = 0; i < N; i++) {
                result[i] = data[i] + other.data[i];
            }
            return result;
        }
        Array operator -(const Array<T, N>& other) const {
            Array result;
            for (int i = 0; i < N; i++) {
                result[i] = data[i] - other.data[i];
            }
            return result;
        }
    };
};

template<typename T, int N>
Structures::Array<T, N> operator*(T scalar, const Structures::Array<T, N>& array) {
    Structures::Array<T, N> result;
    for (int i = 0; i < N; i++) {
        result[i] = scalar * array[i];
    }
    return result;
}

template<typename T, int N>
std::ostream& operator<<(std::ostream& os, const Structures::Array<T, N>& array) {
    os << "[";
    for (int i = 0; i < N; i++) {
        os << array[i];
        if (i != N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}