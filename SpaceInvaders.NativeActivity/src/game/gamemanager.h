#pragma once

#include <core/app.h>
#include <util/list.h>
#include <graphics/render/renderer.h>
#include <game/entity/player.h>

#define GAME_AREA_HEIGHT 1000.0f 
#define GAME_AREA_WIDTH (GAME_AREA_HEIGHT * NativeApp::GetAspectRatio())


class GameManager {
public:
	Player* player;

	Renderer* renderer;

public:
	GameManager();
	//GameManager(GameManagerInstance*);
	~GameManager();

	void Update(float delta, float input_x, float input_y);
	void Render();
};