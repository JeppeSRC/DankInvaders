#include "projectile_default.h"
#include <game/entity/ship.h>

ProjectileDefault::ProjectileDefault(Ship* shooter) : Projectile(shooter->GetPosition(), vec2(20, 20), shooter) {
	damage = 1.0f;
	speed = 100.0f;

	
}