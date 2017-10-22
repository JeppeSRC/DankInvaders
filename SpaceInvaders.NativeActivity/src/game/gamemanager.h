#pragma once

#include <core/app.h>
#include <util/list.h>
#include <graphics/render/renderer.h>
#include <game/entity/player.h>
#include <vector>
#include <game/menu/menu.h>

class GameManager {
public:
	Menu* mainMenu;
	Menu* gameMenu;
	Menu* activeMenu;
	Player* player;

	List<Entity*> entities;
	List<Entity*> removedEntities;

	Renderer* renderer;

	vec2 inputCoord;
public:
	GameManager();
	//GameManager(GameManagerInstance*);
	~GameManager();

	void Add(Entity* e);
	void Remove(Entity* e);

	void Update(float delta);
	void Render();
};