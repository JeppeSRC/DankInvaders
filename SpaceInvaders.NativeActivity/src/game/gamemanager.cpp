#include "gamemanager.h"

#include <game/entity/npc/aiship_default.h>

Font* font;

GameManager::GameManager() : inputCoord(-1.0f, -1.0f){
	player = new Player(vec3(GAME_AREA_WIDTH / 2.0f, GAME_AREA_HEIGHT - 35 - 50, 0), this);

	renderer = Renderer::CreateRenderer(512);

	entities.Push_back(player);
	entities.Push_back(new AIShipDefault(vec3(100, 50, 0), vec2(100, 100), this));

	font = new Font("fonts/AndroidClock.ttf", 10);
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
	renderer->Begin();

	size_t size = entities.GetSize();

	for (size_t i = 0; i < size; i++) {
		renderer->Submit(entities[i]);
	}

	renderer->Submit("0123456789", font, vec2(50, 100));

	renderer->End();
	renderer->Present();
}