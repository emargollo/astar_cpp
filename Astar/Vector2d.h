#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>
#include <sstream>

template<class V>
class Vector2d
{
public:
	Vector2d() {}
	Vector2d(V x, V y) {
		m_x = x;
		m_y = y;
	}
	~Vector2d() {}
	V X() const { return m_x; }
	V Y() const { return m_y; }
	Vector2d<V> X(V x) {
		m_x = x;
		return this;
	}
	Vector2d<V> Y(V y) {
		m_y = y;
		return this;
	}
	Vector2d<V> set(V x, V y) {
		m_x = x;
		m_y = y;
		return this;
	}

	friend bool operator == (const Vector2d &lhs, const Vector2d &rhs) {
		return (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y);
	}

	static double Distance(Vector2d lhs, Vector2d rhs) {
		return std::sqrt(std::pow((lhs.X() - rhs.X()), 2) + std::pow((lhs.Y() - rhs.Y()), 2));
	}

	std::string toString() {
		std::stringstream ss;
		ss << "(" << m_x << ", " << m_y << ")";
		return ss.str();
	}

private:
	V m_x;
	V m_y;
};

#endif

