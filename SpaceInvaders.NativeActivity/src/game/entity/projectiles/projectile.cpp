#include "projectile.h"
#include <game/entity/ship.h>
#include <game/gamemanager.h>

Projectile::Projectile(vec3 position, vec2 size, Ship* shooter, PROJECTILE_TYPE type, GameManager* manager) : Entity(position, size, ENTITY_TYPE_PROJECTILE, manager), type(type), shooter(shooter) {

}

Projectile::Projectile(const Projectile* other) : Entity(other->shooter->GetPosition(), other->size, ENTITY_TYPE_PROJECTILE, other->manager), type(other->type), damage(other->damage), speed(other->speed), direction(other->direction), shooter(other->shooter) {

}

void Projectile::Update(float delta) {
	position.y += delta * direction.y * speed;

	if (position.y <= -size.y / 2.0f) {
		manager->Remove(this);
		return;
	}

	List<Entity*>& entities = manager->entities;

	size_t numEntities = entities.GetSize();

	for (size_t i = 0; i < numEntities; i++) {
		Entity* e = entities[i];

		if (e->GetType() != ENTITY_TYPE_SHIP) continue;

		if (Intersects(e)) {
			Ship* ship = (Ship*)e;
			
			ship->OnHit(this);
		}
	}
}