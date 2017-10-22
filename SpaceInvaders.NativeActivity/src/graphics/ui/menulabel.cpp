#include "menulabel.h"

MenuLabel::MenuLabel(const vec3& position, const vec2& size, const String& title) : MenuItem(position, size, title) {

}

void MenuLabel::Render(Renderer* renderer) {
	vec2 textSize = Font::currentFont->GetFontMetrics(title);

	textSize.y *= 0.5f;
	textSize.x *= -0.5f;

	renderer->Submit(title, Font::currentFont, vec2(position) + textSize, 0xFF00FF);
}