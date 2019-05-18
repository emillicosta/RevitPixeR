#include <cmath>        // sqrt, fabs
#include <iostream>     // cout, cin, endl
#include <cassert>      // assert()
#include <initializer_list> // initializer_list
#include <algorithm>    // copy
#include <iomanip>      // setprecision()
#pragma once
class Vec3
{
public:
	typedef float value_type;
	enum field_t { X = 0, Y = 1, Z = 2, R = 0, G = 1, B = 2 };

	value_type e[3];
	explicit Vec3(float e0_ = 0.f, float e1_ = 0.f, float e2_ = 0.f)
		: e{ e0_, e1_, e2_ }
	{ /* empty */}

	Vec3(const Vec3& other_)
		: e{ other_.e[X], other_.e[Y], other_.e[Z] }
	{ /* empty */
	}

	Vec3(std::initializer_list< value_type > il_)
	{
		assert(il_.size() >= 3);
		std::copy(il_.begin(), std::next(il_.begin(), 3), std::begin(e));
	}

	//=== Access operators
	inline value_type x() const { return e[X]; }
	inline value_type y() const { return e[Y]; }
	inline value_type z() const { return e[Z]; }
	inline value_type r() const { return e[R]; }
	inline value_type g() const { return e[G]; }
	inline value_type b() const { return e[B]; }

	// indexed access operator (rhs)
	inline value_type operator[](size_t idx) const { return e[idx]; }
	// indexed access operator (lhs)
	inline value_type& operator[](size_t idx) { return e[idx]; }

	//=== Algebraic operators

	bool operator==(const Vec3& other_) const
	{
		return fabs(e[X] - other_.e[X]) < 0.00001f &&
			fabs(e[Y] - other_.e[Y]) < 0.00001f &&
			fabs(e[Z] - other_.e[Z]) < 0.00001f;
	}

	Vec3 & operator=(const Vec3 & other_)
	{
		e[X] = other_.e[X];
		e[Y] = other_.e[Y];
		e[Z] = other_.e[Z];
		return *this;
	}

	Vec3& operator=(std::initializer_list< value_type > il_)
	{
		assert(il_.size() >= 3);
		std::copy(il_.begin(), std::next(il_.begin(), 3), std::begin(e));
		return *this;
	}


	// Unary '+'
	inline const Vec3& operator+(void) const { return *this; }
	// Unary '-'
	inline Vec3 operator-(void) const { return Vec3(-e[X], -e[Y], -e[Z]); }

	inline Vec3& operator+=(const Vec3&);
	inline Vec3& operator-=(const Vec3&);
	inline Vec3& operator*=(const Vec3&);
	inline Vec3& operator/=(const Vec3&);
	inline Vec3& operator*=(const value_type);
	inline Vec3& operator/=(const value_type);

	inline value_type length(void) const
	{
		return sqrt(e[X] * e[X] + e[Y] * e[Y] + e[Z] * e[Z]);
	}
	inline value_type squared_length(void) const
	{
		return (e[X] * e[X] + e[Y] * e[Y] + e[Z] * e[Z]);
	}
	inline void make_unit_vector(void);

	inline void printRGB(void) const {
		std::cout << "( " << e[R] << ", " << e[G] << ", " << e[B] << " )" << std::endl;
	}

	inline void printPoint(void) const {
		std::cout << "( " << e[X] << ", " << e[Y] << ", " << e[Z] << " )" << std::endl;
	}

	inline void printVec3(void) const {
		std::cout << "( " << e[X] << ", " << e[Y] << ", " << e[Z] << " )" << std::endl;
	}

};
typedef Vec3 rgb;
typedef Vec3 offset;
typedef Vec3 point3;
typedef Vec3 vec3;

inline void Vec3::make_unit_vector(void)
{
	/**
	 * +---> unit vector.
	 * |
	 *
	 * ^     1
	 * v = _____ * v
	 *     ||v||
	 *
	 * ||v|| = sqrt( v dot v )
	 *
	 *      1
	 * k =_____
	 *    ||v||
	 */
	auto v_dot_v = e[X] * e[X] + e[Y] * e[Y] + e[Z] * e[Z];
	// make sure we divide by zero here.
	assert(fabs(v_dot_v - 0.f) > 0.000001);
	value_type k = 1.f / sqrt(v_dot_v);
	e[X] *= k;
	e[Y] *= k;
	e[Z] *= k;
}

//
//=== Non-member function implementation: operator overloading.
//

inline std::istream& operator>>(std::istream & is, Vec3 & v)
{
	is >> v.e[Vec3::field_t::X]
		>> v.e[Vec3::field_t::Y]
		>> v.e[Vec3::field_t::Z];
	return is;
}

inline std::ostream& operator<<(std::ostream & os, const Vec3 & v)
{
	os << std::fixed << std::setprecision(2)
		<< "{ "
		<< v.e[Vec3::field_t::X]
		<< " "
		<< v.e[Vec3::field_t::Y]
		<< " "
		<< v.e[Vec3::field_t::Z]
		<< " }";

	return os;
}

inline Vec3 operator+(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[Vec3::X] + v2.e[Vec3::X],
		v1.e[Vec3::Y] + v2.e[Vec3::Y],
		v1.e[Vec3::Z] + v2.e[Vec3::Z]);
}

inline Vec3 operator-(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[Vec3::X] - v2.e[Vec3::X],
		v1.e[Vec3::Y] - v2.e[Vec3::Y],
		v1.e[Vec3::Z] - v2.e[Vec3::Z]);
}

inline Vec3 operator*(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[Vec3::X] * v2.e[Vec3::X],
		v1.e[Vec3::Y] * v2.e[Vec3::Y],
		v1.e[Vec3::Z] * v2.e[Vec3::Z]);
}

inline Vec3 operator/(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[Vec3::X] / v2.e[Vec3::X],
		v1.e[Vec3::Y] / v2.e[Vec3::Y],
		v1.e[Vec3::Z] / v2.e[Vec3::Z]);
}

inline Vec3 operator*(const Vec3 & v, Vec3::value_type t)
{
	return Vec3(v.e[Vec3::X] * t,
		v.e[Vec3::Y] * t,
		v.e[Vec3::Z] * t);
}

inline Vec3 operator*(Vec3::value_type t, const Vec3 & v)
{
	return Vec3(v.e[Vec3::X] * t,
		v.e[Vec3::Y] * t,
		v.e[Vec3::Z] * t);
}

inline Vec3 operator/(const Vec3 & v, Vec3::value_type t)
{
	return Vec3(v.e[Vec3::X] / t,
		v.e[Vec3::Y] / t,
		v.e[Vec3::Z] / t);
}

inline Vec3::value_type dot(const Vec3 & v1, const Vec3 & v2)
{
	return v1.e[Vec3::X] * v2.e[Vec3::X] +
		v1.e[Vec3::Y] * v2.e[Vec3::Y] +
		v1.e[Vec3::Z] * v2.e[Vec3::Z];
}

inline Vec3 cross(const Vec3 & v1, const Vec3 & v2)
{
	return Vec3(v1.e[Vec3::Y] * v2.e[Vec3::Z] - v1.e[Vec3::Z] * v2.e[Vec3::Y],
		-(v1.e[Vec3::X] * v2.e[Vec3::Z] - v1.e[Vec3::Z] * v2.e[Vec3::X]),
		v1.e[Vec3::X] * v2.e[Vec3::Y] - v1.e[Vec3::Y] * v2.e[Vec3::X]);
}

inline Vec3 & Vec3::operator+=(const Vec3 & v)
{
	e[X] += v.e[X];
	e[Y] += v.e[Y];
	e[Z] += v.e[Z];

	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 & v)
{
	e[X] -= v.e[X];
	e[Y] -= v.e[Y];
	e[Z] -= v.e[Z];

	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 & v)
{
	e[X] *= v.e[X];
	e[Y] *= v.e[Y];
	e[Z] *= v.e[Z];

	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 & v)
{
	e[X] /= v.e[X];
	e[Y] /= v.e[Y];
	e[Z] /= v.e[Z];

	return *this;
}

inline Vec3& Vec3::operator*=(const value_type t)
{
	e[X] *= t;
	e[Y] *= t;
	e[Z] *= t;

	return *this;
}

inline Vec3& Vec3::operator/=(const value_type t)
{
	assert(fabs(t - 0.f) > 0.000001);
	value_type k = 1.f / t;

	e[X] *= k;
	e[Y] *= k;
	e[Z] *= k;

	return *this;
}

inline static Vec3 unit_vector(const Vec3 & v)
{
	return v / v.length();
}

inline static Vec3 min_vector(const Vec3 & v, const Vec3 & u)
{
	Vec3 aux = Vec3(0, 0, 0);
	if (v.x() < u.x())
	{
		aux[0] = v[0];
	}
	else {
		aux[0] = u[0];
	}

	if (v.y() < u.y())
	{
		aux[1] = v[1];
	}
	else {
		aux[1] = u[1];
	}

	if (v.z() < u.z())
	{
		aux[2] = v[2];
	}
	else {
		aux[2] = u[2];
	}

	return aux;
}

inline static Vec3 max_vector(const Vec3 & v, const Vec3 & u)
{
	Vec3 aux = Vec3(0, 0, 0);
	if (v.x() > u.x())
	{
		aux[0] = v[0];
	}
	else {
		aux[0] = u[0];
	}

	if (v.y() > u.y())
	{
		aux[1] = v[1];
	}
	else {
		aux[1] = u[1];
	}

	if (v.z() > u.z())
	{
		aux[2] = v[2];
	}
	else {
		aux[2] = u[2];
	}

	return aux;
}

