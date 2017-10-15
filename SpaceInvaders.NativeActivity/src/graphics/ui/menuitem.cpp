#include "menuitem.h"


MenuItem::MenuItem(const vec3& position) : position(position), color(1, 1, 1, 1), texture(nullptr), title("") { }

bool MenuItem::OnPress() { }

bool MenuItem::OnRelease() { }