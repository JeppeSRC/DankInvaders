#include "player.h"

#include <game/gamemanager.h>
#include <game/entity/weapon/weapon_default.h>
#include <game/entity/projectiles/projectile_default.h>

Player::Player(vec3 position, GameManager* manager) : Ship(position, vec2(50, 50), SHIP_TYPE_PLAYER, manager) {
	color = vec4(1, 1, 0, 1);
	weapon = new WeaponDefault(new ProjectileDefault(this, manager), manager);
}

void Player::Update(float delta) {
	vec2& inputCoord = manager->inputCoord;

	if (inputCoord.x >= 0) {
		if ((unsigned int)inputCoord.x > NativeApp::app->surface_width >> 1) {
			position.x += 300.0 * delta;
		}
		else {
			position.x -= 300.0 * delta;
		}

		CLAMP(position.x, size.x / 2.0f, GAME_AREA_WIDTH - size.x / 2.0f);
	}

	weapon->Update(delta);
}