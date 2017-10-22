#pragma once

#include "menuitem.h"

class MenuLabel : public MenuItem {
private:

public:
	MenuLabel(const vec3& position, const vec2& size, const String& title);
	
	void Render(Renderer* renderer) override;
};
