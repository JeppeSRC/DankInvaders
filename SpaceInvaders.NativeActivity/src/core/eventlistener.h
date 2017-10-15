#pragma once


class EventListener {
public:

	virtual bool OnPress(float x, float y) = 0;
	virtual bool OnMove(float x, float y) = 0;
	virtual bool OnRelease() = 0;
};
