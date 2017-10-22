#pragma once

#include "menu.h"
#include <graphics/font/font.h>


class MainMenu : public Menu {
public:
	MainMenu();
	~MainMenu();

	void Render() override;
	void Update(float delta) override;

};
