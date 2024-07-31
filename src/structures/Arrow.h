#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include "Point.h"

namespace Structures {
	enum class WHERE_ON_ARROW {
		START,
		END,
	};

	template<typename T>
	struct Arrow {
		Point<T> start;
		Point<T> end;

		/**
		 * @brief Normalize the arrow - adjust the arrow to have the same direction but with length 1.
		 * This is not an in-place operation.
		 * @return Arrow The normalized arrow
		*/
		Arrow<T> getNormalized() const {
			T length = this->getLength();
			if (length == 0) length = 1; // To avoid division by zero, though logically length should never be 0 here.
			return { this->start, { this->start.x + (this->end.x - this->start.x) / length, this->start.y + (this->end.y - this->start.y) / length } };
		}
			
		double getAngle() const {
			return this->end.angleTo(this->start);
		}

		/**
		 * @brief Move the arrow to the origin.
		 * This is not an in-place operation.
		 * @return Arrow The arrow moved to the origin
		*/
		Arrow<T> moveToOrigin() const {
			return { {0, 0}, this->end - this->start };
		}

		/**
		 * @brief Move the arrow to a new base point.
		 * This is not an in-place operation.
		 * @param base The new base point
		 * @return Arrow The arrow moved to the new base point
		*/
		Arrow<T> moveBase(Point<T> base) const {
			const Arrow<T> thisArrow = this->moveToOrigin();
			return { base, thisArrow.end + base };
		}
		/**
		 * @brief Get the length of the arrow
		 * @return double The length of the arrow
		*/
		T getLength() const {
			return sqrt(pow(this->end.x - this->start.x, 2) + pow(this->end.y - this->start.y, 2));
		}

		/**
		 * @brief Add another arrow to this arrow, preserving the start point of the lhs arrow
		 * @param other The arrow to add
		 * @return Arrow The arrow with the other arrow added
		*/
		Arrow<T> operator+(const Arrow<T>& other) const {
			return { this->start, this->end + other.end };
		}

		/**
		 * @brief Subtract another arrow from this arrow, preserving the start point of the lhs arrow
		 * @param other The arrow to subtract
		 * @return Arrow The arrow with the other arrow subtracted
		*/
		Arrow<T> operator-(const Arrow<T>& other) const {
			return { this->start, this->end - other.end };
		}

		/**
		 * @brief Add another arrow to this arrow, preserving the start point of the lhs arrow
		 * @param other The arrow to add
		 * @return Arrow The arrow with the other arrow added
		*/
		Arrow<T> operator+=(const Arrow<T>& other) {
			this->end.x += other.end.x;
			this->end.y += other.end.y;
			return *this;
		}

		/**
		 * @brief Scale the arrow by a scalar, preserving the start point
		 * @param scalar The scalar to scale the arrow with
		 * @return Arrow The scaled arrow
		*/
		Arrow<T> operator*(double scalar) const {
			return { this->start, { this->start.x + (this->end.x - this->start.x) * scalar, this->start.y + (this->end.y - this->start.y) * scalar } };
		}

		/**
		 * @brief Get the two perpendicular arrows with same start/end[where] point and length as the original arrow
		 * @return two arrows that are perpendicular to the original arrow (theese point in oposite directions of each other)
		*/
		std::array<Arrow<T>, 2> getPerpendiculars(WHERE_ON_ARROW where) const {
			Arrow<T> arrow1;
			Arrow<T> arrow2;
			switch (where) {
			case WHERE_ON_ARROW::START:
				arrow1 = { this->start, { this->start.x + this->end.y - this->start.y, this->start.y - this->end.x + this->start.x } };
				arrow2 = { this->start, { this->start.x - this->end.y + this->start.y, this->start.y + this->end.x - this->start.x } };
				break;
			case WHERE_ON_ARROW::END:
				arrow1 = { this->end, { this->end.x + this->end.y - this->start.y, this->end.y - this->end.x + this->start.x } };
				arrow2 = { this->end, { this->end.x - this->end.y + this->start.y, this->end.y + this->end.x - this->start.x } };
				break;
			}
			return { arrow1, arrow2 };
		}
	};

	/**
	 * @brief Scale the arrow by a scalar, preserving the start point
	 * @param scalar The scalar to scale the arrow with
	 * @param arrow The arrow to scale
	 * @return Arrow The scaled arrow
	*/
	template<typename T>
	Arrow<T> operator*(T scalar,const Arrow<T>& arrow) {
		return { arrow.start, { arrow.start.x + (arrow.end.x - arrow.start.x) * scalar, arrow.start.y + (arrow.end.y - arrow.start.y) * scalar } };
	}
}



template<typename T>
std::ostream& operator<<(std::ostream& os, const Structures::Arrow<T>& arrow) {
	os << "Arrow: " << arrow.start << " -> " << arrow.end;
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (int i = 0; i < vec.size(); i++) {
		os << vec.at(i);
		if (i != vec.size() - 1) os << "\n";
	}
	os << "]";
	return os;
}