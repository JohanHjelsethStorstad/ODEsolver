#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace Structures {
	template<typename T>
	struct Point {
		T x;
		T y;

		Point() : x{0}, y{0} { }
		Point(T x, T y) : x{x}, y{y} { }

		/**
		 * @brief convert the point to a point with a different type
		*/
		template<typename U>
		Point(const Point<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

		bool operator==(const Point<T>& other) const {
			return this->x == other.x && this->y == other.y;
		}
		Point<T> operator+(const Point<T>& other) const {
			return { this->x + other.x, this->y + other.y };
		}
		Point<T> operator-(const Point<T>& other) const {
			return { this->x - other.x, this->y - other.y };
		}
		float distanceTo(const Point<T>& other) const {
			return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
		}
		float angleTo(const Point<T>& other) const {
			return atan2(other.y - this->y, other.x - this->x);
		}
	};
};

template<typename T>
Structures::Point<T> operator*(T scalar, const Structures::Point<T>& point) {
    return { point.x * scalar, point.y * scalar };
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Structures::Point<T>& point) {
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}