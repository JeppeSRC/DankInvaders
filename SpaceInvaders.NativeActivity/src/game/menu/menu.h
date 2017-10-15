#pragma once

#include <util/list.h>
#include <util/string.h>
#include <graphics/ui/menuitem.h>
#include <core/event.h>

class Menu : public EventListener {
protected:
	String name;

	List<MenuItem*> items;

	bool paused;

	Menu();
public:
	
	
	inline bool IsPaused() const { return paused; }
	inline String& GetName() { return name; }
};