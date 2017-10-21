#include "menu.h"

Menu::Menu(const String& name) : name(name) {
	renderer = Renderer::CreateRenderer(64);
}

Menu::~Menu() {
	delete renderer;
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

void Menu::Update() {

}

bool Menu::OnPress(float x, float y) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		MenuItem& item = *items[i];

		if (item.IsPointInside(vec2(x, y))) {
			item.OnPress(x, y);
		}
	}
}

bool Menu::OnMove(float x, float y) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		MenuItem& item = *items[i];

		if (item.IsPointInside(vec2(x, y))) {
			vec3 tmp = item.GetPosition() - item.GetSize() / 2.0f;
			item.OnMove(x - tmp.x, y - tmp.y);
		}
	}
}

bool Menu::OnRelease() {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {

	}
}