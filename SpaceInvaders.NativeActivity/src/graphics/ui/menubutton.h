#pragma once

#include "menuitem.h"

class MenuButton : public MenuItem {
protected:
	vec2 textPosition;
public:
	MenuButton(const vec3& position, const vec2& size, const String& title);

	void Render(Renderer* renderer) override;

	virtual bool OnPress(const vec2& pos) override;
	virtual bool OnRelease() override;
};