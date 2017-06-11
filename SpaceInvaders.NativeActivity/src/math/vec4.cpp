#include "vec4.h"
#include <memory>


vec4::vec4() : vec4(0, 0, 0, 0) {}

vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

#ifndef __arm__

vec4& vec4::Add(const vec4& v) {
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	_mm_store_ps((float*)this, xmm);
	return *this;
}

vec4& vec4::Add(float v) {
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_add_ps(xmm, _mm_set_ps(v, v, v, v));
	_mm_store_ps((float*)this, xmm);
	return *this;
}

vec4& vec4::Subtract(const vec4& v) {
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	_mm_store_ps((float*)this, xmm);	
	return *this;
}

vec4& vec4::Subtract(float v) {
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_sub_ps(xmm, _mm_set_ps(v, v, v, v));
	_mm_store_ps((float*)this, xmm);
	return *this;
}

vec4& vec4::Multiply(const vec4& v) {
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	_mm_store_ps((float*)this, xmm);	
	return *this;
}

vec4& vec4::Multiply(float v) {
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_mul_ps(xmm, _mm_set_ps(v, v, v, v));
	_mm_store_ps((float*)this, xmm);	
	return *this;
}

vec4& vec4::Divide(const vec4& v) {
	__m128 vxmm = _mm_set_ps(v.w, v.z, v.y, v.x);
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_div_ps(xmm, vxmm);
	_mm_store_ps((float*)this, xmm);	
	return *this;
}

vec4& vec4::Divide(float v) {
	__m128 xmm = _mm_set_ps(w, z, y, x);
	xmm = _mm_div_ps(xmm, _mm_set_ps(v, v, v, v));
	_mm_store_ps((float*)this, xmm);	
	return *this;
}

#else 

vec4& vec4::Add(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Add(float v) {
	x += v;
	y += v;
	z += v;
	w += v;
	return *this;
}

vec4& vec4::Subtract(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Subtract(float v) {
	x -= v;
	y -= v;
	z -= v;
	w += v;
	return *this;
}

vec4& vec4::Multiply(const vec4& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Multiply(float v) {
	x *= v;
	y *= v;
	z *= v;
	w += v;
	return *this;
}

vec4& vec4::Divide(const vec4& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w += v.w;
	return *this;
}

vec4& vec4::Divide(float v) {
	x /= v;
	y /= v;
	z /= v;
	w += v;
	return *this;
}

#endif

vec4& vec4::Normalize() {
	return Multiply(1.0f / LengthSqrt());
}

float vec4::Length() const {
	return x * x + y * y + z * z + w * w;
}

float vec4::LengthSqrt() const {
	return sqrtf(Length());
}

bool vec4::operator==(const vec4& v) const {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool vec4::operator!=(const vec4& v) const {
	return !(x == v.x && y == v.y && z == v.z && w == v.w);
}

