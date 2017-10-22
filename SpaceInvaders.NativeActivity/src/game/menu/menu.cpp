#include "menu.h"

Menu::Menu(const String& name) : name(name), pressedItem(nullptr), paused(false) {
	renderer = Renderer::CreateRenderer(512);
	EventDispatcher::AddListener(this);
}

Menu::~Menu() {
	delete renderer;
	EventDispatcher::RemoveListener(this);
}

void Menu::Render() {
	renderer->Begin();
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->Render(renderer);
	}

	renderer->End();
	renderer->Present();
}

void Menu::Update(float delta) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->Update(delta);
	}
}

bool Menu::OnPress(const vec2& pos) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		MenuItem* item = items[i];

		if (item->IsPointInside(pos)) {
			const vec2& size = item->GetSize();
			vec2 tmp = vec2(item->GetPosition()) - size / 2.0f;
			item->OnPress(pos - vec2(tmp));
			pressedItem = item;
			break;
		}
	}
}

bool Menu::OnMove(const vec2& pos) {
	if (pressedItem != nullptr) {
		if (pressedItem->IsPointInside(pos)) {
			const vec2& size = pressedItem->GetSize();
			vec2 tmp = vec2(pressedItem->GetPosition()) - size / 2.0f;
			pressedItem->OnMove(pos - tmp);
		}
	}
}

bool Menu::OnRelease() {
	if (pressedItem) {
		pressedItem->OnRelease();
		pressedItem = nullptr;
	}
}