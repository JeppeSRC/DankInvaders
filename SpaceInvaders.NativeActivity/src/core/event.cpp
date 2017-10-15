#include "event.h"

List<EventListener*> EventDispatcher::listeners;

void EventDispatcher::AddListener(EventListener* listener) {
	listeners << listener;
}

void EventDispatcher::RemoveListener(EventListener* listener) {
	listeners.Remove(listener);
}

void EventDispatcher::OnPress(float x, float y) {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnPress(x, y);
	}
}

void EventDispatcher::OnMove(float x, float y) {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnMove(x, y);
	}
}

void EventDispatcher::OnRelease() {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnRelease();
	}
}