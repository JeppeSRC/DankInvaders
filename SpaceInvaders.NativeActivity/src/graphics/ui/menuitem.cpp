#include "menuitem.h"


MenuItem::MenuItem(const vec3& position, const vec2& size, const String& title) : position(position), size(size), color(1, 1, 1, 1), texture(nullptr), title(title) { }

bool MenuItem::OnPress(const vec2& pos) { }

bool MenuItem::OnMove(const vec2& pos) { }

bool MenuItem::OnRelease() { }

void MenuItem::Update(float delta) { }

bool MenuItem::IsPointInside(const vec2& point) const {
	vec2 tl = vec2(position) - size / 2.0f;
	vec2 br = vec2(position) + size / 2.0f;

	return tl < point && br > point;
}