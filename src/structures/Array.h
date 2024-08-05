#pragma once
#include <array>
#include "Point.h"

namespace Structures {
    template<typename T, std::size_t N>
    class Array : public std::array<T, N> {
    public:
        using std::array<T, N>::array;

        Array(const Structures::Point<T>& point) {
            static_assert(N == 2, "This constructor is only valid for arrays of size 2.");
            (*this)[0] = point.x;
            (*this)[1] = point.y;
        }
    };
}