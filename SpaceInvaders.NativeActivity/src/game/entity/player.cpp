#include "player.h"

#include <game/gamemanager.h>
#include <game/entity/weapon/weapon_default.h>
#include <game/entity/projectiles/projectile_default.h>

Player::Player(vec3 position) : Ship(position, vec2(50, 50), SHIP_TYPE_PLAYER) {
	color = vec4(1, 1, 0, 1);
	weapon = new WeaponDefault(new ProjectileDefault(this));
}

void Player::Update(float delta, GameManager* manager) {
	vec2& inputCoord = manager->inputCoord;

	if (inputCoord.x >= 0) {
		if ((unsigned int)inputCoord.x > NativeApp::app->surface_width >> 1) {
			position.x += 300.0 * delta;
		}
		else {
			position.x -= 300.0 * delta;
		}

		CLAMP(position.x, 0, GAME_AREA_WIDTH - size.x);
	}

	weapon->Update(delta, manager);
}