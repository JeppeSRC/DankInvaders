#include "gamemanager.h"

GameManager::GameManager() {
	player = new Player(vec3(GAME_AREA_WIDTH / 2.0f, GAME_AREA_HEIGHT - (GAME_AREA_HEIGHT * 0.05f) - 10, 0));

	renderer = new Renderer(512);
}

GameManager::~GameManager() {
	delete player;
	delete renderer;
}

void GameManager::Update(float delta, float input_x, float input_y) {
	vec3& pPos = player->GetPosition();
	vec2& pSize = player->GetSize();

	
}

void GameManager::Render() {
	renderer->Begin();
	renderer->Submit(player);

	size_t size = aliens.GetSize();

	for (size_t i = 0; i < size; i++) {
		renderer->Submit(aliens[i]);
	}

	renderer->End();
	renderer->Present();
}