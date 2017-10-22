#include "event.h"

List<EventListener*> EventDispatcher::listeners;

void EventDispatcher::AddListener(EventListener* listener) {
	listeners << listener;
}

void EventDispatcher::RemoveListener(EventListener* listener) {
	listeners.Remove(listener);
}

void EventDispatcher::OnPress(vec2 pos) {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnPress(pos);
	}
}

void EventDispatcher::OnMove(vec2 pos) {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnMove(pos);
	}
}

void EventDispatcher::OnRelease() {
	size_t size = listeners.GetSize();

	for (size_t i = 0; i < size; i++) {
		listeners[i]->OnRelease();
	}
}