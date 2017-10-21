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

	bool paused;

	Menu(const String& name);
public:
	virtual ~Menu();
	
	void Render();
	void Update();

	bool OnPress(float x, float y) override;
	bool OnMove(float x, float y) override;
	bool OnRelease() override;
	
	inline bool IsPaused() const { return paused; }
	inline String& GetName() { return name; }
};