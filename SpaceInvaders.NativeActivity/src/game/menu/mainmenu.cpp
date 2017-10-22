#include "mainmenu.h"

#include <graphics/ui/menulabel.h>
#include <graphics/ui/menubutton.h>

MainMenu::MainMenu() : Menu("Main Menu") {
	
	items.Push_back(new MenuButton(vec3(GAME_AREA_WIDTH / 2.0f, 300, 0), vec2(0, 0), "Play"));
	paused = true;
}

MainMenu::~MainMenu() {

}

void MainMenu::Render() {
	renderer->Begin();

	renderer->Submit(name, Font::currentFont, vec2(GAME_AREA_WIDTH / 2.0f - Font::currentFont->GetFontMetrics(name).x / 2.0f, Font::currentFont->GetFontMetrics(name).y + 20), 0xFFFFFF);


	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->Render(renderer);
	}

	renderer->End();
	renderer->Present();
}

void MainMenu::Update(float delta) {
	size_t size = items.GetSize();

	for (size_t i = 0; i < size; i++) {
		items[i]->Update(delta);
	}
}