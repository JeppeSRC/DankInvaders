#include "mathcommon.h"
#include "vec2.h"
#include <memory>


vec2::vec2() { x = 0; y = 0; }
vec2::vec2(float x, float y) { this->x = x; this->y = y; }

#if !(defined(__arm__) || defined(__aarch64__))

vec2& vec2::Add(const vec2& v) {
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_add_ps(xmm, vxmm);
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Add(float v) {
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_add_ps(xmm, _mm_set_ps(0, 0, v, v));
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Subtract(const vec2& v) {
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_sub_ps(xmm, vxmm);
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Subtract(float v) {
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_sub_ps(xmm, _mm_set_ps(0, 0, v, v));
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Multiply(const vec2& v) {
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_mul_ps(xmm, vxmm);
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Multiply(float v) {
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_mul_ps(xmm, _mm_set_ps(0, 0, v, v));
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Divide(const vec2& v) {
	__m128 vxmm = _mm_set_ps(0, 0, v.y, v.x);
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_div_ps(xmm, vxmm);
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

vec2& vec2::Divide(float v) {
	__m128 xmm = _mm_set_ps(0, 0, y, x);
	xmm = _mm_div_ps(xmm, _mm_set_ps(1, 1, v, v));
	float tmp[4];
	_mm_store_ps(tmp, xmm);
	memcpy(this, tmp, sizeof(float) * 2);
	return *this;
}

#else

vec2& vec2::Add(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

vec2& vec2::Add(float v) {
	x += v;
	y += v;
	return *this;
}

vec2& vec2::Subtract(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

vec2& vec2::Subtract(float v) {
	x -= v;
	y -= v;
	return *this;
}

vec2& vec2::Multiply(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

vec2& vec2::Multiply(float v) {
	x *= v;
	y *= v;
	return *this;
}

vec2& vec2::Divide(const vec2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

vec2& vec2::Divide(float v) {
	x /= v;
	y /= v;
	return *this;
}

#endif

vec2& vec2::Normalize() {
	return Multiply(1.0f / LengthSqrt());
}

float vec2::Length() const {
	return x * x + y * y;
}

float vec2::LengthSqrt() const {
	return sqrtf(Length());
}

vec2& vec2::RotateZ(float angle) {
	float a = FD_TO_RADIANS_F(angle);

	float _x = x * cosf(a) - y * sinf(a);
	float _y = y * cosf(a) + x * sinf(a);

	x = _x;
	y = _y;

	return *this;
}

bool vec2::operator==(const vec2& v) const {
	return x == v.x && y == v.y;
}

bool vec2::operator!=(const vec2& v) const {
	return !(x == v.x && y == v.y);
}

bool vec2::operator>(const vec2& v) const {
	return x > v.x && y > v.y;
}

bool vec2::operator<(const vec2& v) const {
	return x < v.x && y < v.y;
}

bool vec2::operator>=(const vec2& v) const {
	return x >= v.x && y >= v.y;
}

bool vec2::operator<=(const vec2& v) const {
	return x <= v.x && y <= v.y;
}