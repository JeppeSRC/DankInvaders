#pragma once

#include <util/list.h>
#include "eventlistener.h"
#include <math/vec2.h>

class EventDispatcher {
private:
	static List<EventListener*> listeners;
public:
	static void AddListener(EventListener* listener);
	static void RemoveListener(EventListener* listener);

	static void OnPress(vec2 pos);
	static void OnMove(vec2 pos);
	static void OnRelease();
};