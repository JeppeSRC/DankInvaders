#include "gamemanager.h"
#include <game/menu/mainmenu.h>
#include <game/entity/npc/aiship_default.h>

GameManager::GameManager() : inputCoord(-1.0f, -1.0f){
	player = new Player(vec3(GAME_AREA_WIDTH / 2.0f, GAME_AREA_HEIGHT - 35 - 50, 0), this);

	renderer = Renderer::CreateRenderer(512);

	entities.Push_back(player);
	entities.Push_back(new AIShipDefault(vec3(100, 50, 0), vec2(100, 100), this));
	new Font("fonts/arial.ttf", 64);
	activeMenu = new MainMenu;
}

GameManager::~GameManager() {
	delete player;
	delete renderer;
}

void GameManager::Add(Entity* e) {
	entities.Push_back(e);
}

void GameManager::Remove(Entity* e) {
	removedEntities.Push_back(e);
}

void GameManager::Update(float delta) {
	if (activeMenu->IsPaused()) {
		activeMenu->Update(delta);
		return;
	}

	size_t size = entities.GetSize();

	for (size_t i = 0; i < size; i++) {
		entities[i]->Update(delta);
	}

	size = removedEntities.GetSize();

	for (size_t i = 0; i < size; i++) {
		delete entities.Remove(removedEntities[i]);
	}

	removedEntities.Clear();
}

void GameManager::Render() {
	if (activeMenu->IsPaused()) {
		renderer->Present();
		activeMenu->Render();
		return;
	} 

	renderer->Begin();

	size_t size = entities.GetSize();

	for (size_t i = 0; i < size; i++) {
		renderer->Submit(entities[i]);
	}

	renderer->End();
	renderer->Present();
}