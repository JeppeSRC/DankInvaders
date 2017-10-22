#pragma once

#include <util/list.h>
#include <util/string.h>
#include <graphics/ui/menuitem.h>
#include <core/event.h>

class Menu : public EventListener {
protected:
	Renderer* renderer;
protected:
	String name;

	List<MenuItem*> items;
	MenuItem* pressedItem;

	bool paused;

	Menu(const String& name);
public:
	virtual ~Menu();
	
	virtual void Render();
	virtual void Update(float delta);

	bool OnPress(const vec2& pos) override;
	bool OnMove(const vec2& pos) override;
	bool OnRelease() override;
	
	inline bool IsPaused() const { return paused; }
	inline String& GetName() { return name; }
};