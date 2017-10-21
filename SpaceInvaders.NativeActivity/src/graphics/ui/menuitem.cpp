#include "menuitem.h"


MenuItem::MenuItem(const vec3& position) : position(position), color(1, 1, 1, 1), texture(nullptr), title("") { }

bool MenuItem::OnPress() { }

bool MenuItem::OnRelease() { }

bool MenuItem::IsPointInside(const vec2& point) const {
	vec3 tl = position - size / 2.0f;
	vec3 br = position + size / 2.0f;

	return tl < point && br > point;
}