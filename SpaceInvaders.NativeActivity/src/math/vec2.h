#pragma once
#include "mathcommon.h"

class vec2 {
public:
	float x;
	float y;

public:
	vec2();
	//vec2(__m128 xmm);
	vec2(float x, float y);

	vec2& Add(const vec2& v);
	vec2& Add(float v);
	vec2& Subtract(const vec2& v);
	vec2& Subtract(float v);
	vec2& Multiply(const vec2& v);
	vec2& Multiply(float v);
	vec2& Divide(const vec2& v);
	vec2& Divide(float v);
	vec2& Normalize();

	float Length() const;
	float LengthSqrt() const;

	vec2& RotateZ(float angle);

	inline friend vec2 operator+(const vec2& l, const vec2& r) { return vec2(l).Add(r); }
	inline friend vec2 operator-(const vec2& l, const vec2& r) { return vec2(l).Subtract(r); }
	inline friend vec2 operator*(const vec2& l, const vec2& r) { return vec2(l).Multiply(r); }
	inline friend vec2 operator/(const vec2& l, const vec2& r) { return vec2(l).Divide(r); }

	inline friend vec2 operator+(const vec2& l, float r) { return vec2(l).Add(r); }
	inline friend vec2 operator-(const vec2& l, float r) { return vec2(l).Subtract(r); }
	inline friend vec2 operator*(const vec2& l, float r) { return vec2(l).Multiply(r); }
	inline friend vec2 operator/(const vec2& l, float r) { return vec2(l).Divide(r); }

	inline void operator+=(const vec2& v) { Add(v); }
	inline void operator-=(const vec2& v) { Subtract(v); }
	inline void operator*=(const vec2& v) { Multiply(v); }
	inline void operator/=(const vec2& v) { Divide(v); }

	inline void operator+=(float v) { Add(v); }
	inline void operator-=(float v) { Subtract(v); }
	inline void operator*=(float v) { Multiply(v); }
	inline void operator/=(float v) { Divide(v); }

	bool operator==(const vec2& v) const;
	bool operator!=(const vec2& v) const;

	bool operator>(const vec2& v) const;
	bool operator<(const vec2& v) const;
	bool operator>=(const vec2& v) const;
	bool operator<=(const vec2& v) const;

	inline vec2 operator-() { return vec2(-x, -y); }
};