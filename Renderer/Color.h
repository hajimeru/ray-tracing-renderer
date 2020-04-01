#ifndef _COLOR_H_
#define _COLOR_H_

#include <cassert>
#include <cstring>
#include <cmath>
#include <tuple>
#include "MyMath.h"

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

class Color {
public:
	static const Color BLACK;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

	Color() : r(0), g(0), b(0) {}
	Color(double r, double g, double b) : r(r), g(g), b(b) {}
	// Add
	Color& operator += (const Color& rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}
	friend Color operator + (const Color& lhs, const Color& rhs) {
		Color ret(lhs);
		ret += rhs;
		return ret;
	}

	// Multiply
	Color& operator *= (double value) {
		r *= value;
		g *= value;
		b *= value;
		return *this;
	}

	friend Color operator * (const Color& lhs, double value) {
		Color ret(lhs);
		ret *= value;
		return ret;
	}

	friend Color operator * (double value, const Color& rhs) {
		return rhs * value;
	}

	friend bool operator ==(const Color& lhs, const Color& rhs) {
		return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b);
	}

	inline friend std::ostream& operator<<(std::ostream& os, const Color& c);

	// Modulate
	Color modulate(const Color& rhs) const {
		return Color(r*rhs.r, g*rhs.g, b*rhs.b);
	}

	double r, g, b;
};

const Color Color::BLACK = Color(0, 0, 0);
const Color Color::WHITE = Color(1, 1, 1);
const Color Color::RED = Color(1, 0, 0);
const Color Color::GREEN = Color(0, 1, 0);
const Color Color::BLUE = Color(0, 0, 1);

std::ostream& operator<<(std::ostream& os, const Color& c) {
	os << "[Color:rgb]" << c.r << " "
		<< c.g << " "
		<< c.b << " ";
	return os;
}
#endif // !_COLOR_H_

