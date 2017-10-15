#pragma once

#include <util/list.h>
#include "eventlistener.h"

class EventDispatcher {
private:
	static List<EventListener*> listeners;
public:
	static void AddListener(EventListener* listener);
	static void RemoveListener(EventListener* listener);

	static void OnPress(float x, float y);
	static void OnMove(float x, float y);
	static void OnRelease();
};