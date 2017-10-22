#include "menubutton.h"

MenuButton::MenuButton(const vec3& position, const vec2& size, const String& title) : MenuItem(position, size, title) {
	texture = new Texture2D("textures/ui/button.png");

	this->size = Font::currentFont->GetFontMetrics(title);

	textPosition = vec2(position) - vec2(this->size.x * 0.5f, this->size.y * -0.5f);

	this->size += vec2(125, 30);
}

void MenuButton::Render(Renderer* renderer) {

	vec2 s = size;

	renderer->Submit(position, s, 0xFFFFFFFF, texture);

	s.x *= 0.5f;
	s.y *= -0.5f;

	renderer->Submit(title, Font::currentFont, textPosition, 0xFF00FF);
}

bool MenuButton::OnPress(const vec2& pos) {
	LOGD("Button \"%s\" pressed: OnPress not implemented!", *title);
}

bool MenuButton::OnRelease() {
	LOGD("Button \"%s\" released: OnRelease not implemented!", *title);
}