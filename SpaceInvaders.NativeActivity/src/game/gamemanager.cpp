#include "gamemanager.h"

GameManager::GameManager() {
	player = new Player(vec3(GAME_AREA_WIDTH / 2.0f, GAME_AREA_HEIGHT - (GAME_AREA_HEIGHT * 0.05f) - 10, 0));

	renderer = new Renderer(128);
}

GameManager::~GameManager() {
	delete player;
	delete renderer;
}

void GameManager::Update(float delta, float input_x, float input_y) {
	vec3& pPos = player->GetPosition();
	vec2& pSize = player->GetSize();

	/*if (input_x != -1) {
		if (input_x > NativeApp::app->surface_width >> 1) {
			pPos.x += 0.5f * delta;
		} else {
			pPos.x -= 0.5f * delta;
		}
	}*/

	if (input_x >= 0.0f) pPos.x = input_x;
	if (input_y >= 0.0f) pPos.y = input_y;

	CLAMP(pPos.x, 0, 1920);
	CLAMP(pPos.y, 0, 1080);
}

void GameManager::Render() {
	renderer->Begin();
	renderer->Submit(player);
	renderer->End();
	renderer->Present();
}