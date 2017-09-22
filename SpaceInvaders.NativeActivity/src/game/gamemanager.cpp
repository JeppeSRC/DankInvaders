#include "gamemanager.h"

GameManager::GameManager() {
	player = new Player(vec3(GAME_AREA_WIDTH / 2.0f, GAME_AREA_HEIGHT - 15 - 50, 0));

	renderer = Renderer::CreateRenderer(512);
}

GameManager::~GameManager() {
	delete player;
	delete renderer;
}

void GameManager::Update(float delta, float input_x, float input_y) {
	vec3& pPos = player->GetPosition();
	vec2& pSize = player->GetSize();

	if (input_x >= 0) {
		if ((unsigned int)input_x > NativeApp::app->surface_width >> 1) {
			pPos.x += 10.0 * delta;
		}
		else {
			pPos.x -= 10.0 * delta;
		}

		CLAMP(pPos.x, 0, GAME_AREA_WIDTH - pSize.x);
	}


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