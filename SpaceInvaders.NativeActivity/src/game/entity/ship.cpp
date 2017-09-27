#include "ship.h"
#include <game/gamemanager.h>
#include <game/entity/projectiles/projectile.h>

Ship::Ship(vec3 position, vec2 size, SHIP_TYPE type, GameManager* manager) : Entity(position, size, ENTITY_TYPE_SHIP, manager), type(type) { }

void Ship::OnHit(Projectile* projectile) {
	health -= projectile->GetDamage();

	if (health <= 0.0f) {
		manager->Remove(this);
		manager->Remove(projectile);
	}
}