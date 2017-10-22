#pragma once
#include <math/vec2.h>

class EventListener {
public:

	virtual bool OnPress(const vec2& pos) = 0;
	virtual bool OnMove(const vec2& pos) = 0;
	virtual bool OnRelease() = 0;
};
