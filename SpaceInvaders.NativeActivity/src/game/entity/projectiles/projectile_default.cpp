#include "projectile_default.h"
#include <game/entity/ship.h>
#include <game/gamemanager.h>

ProjectileDefault::ProjectileDefault(Ship* shooter) : Projectile(shooter->GetPosition(), vec2(20, 20), shooter, PROJECTILE_TYPE_DEFAULT) {
	damage = 1.0f;
	speed = 300.0f;

	direction = vec2(0, -1);
}

ProjectileDefault::ProjectileDefault(const ProjectileDefault* other) : Projectile(other) {

}

void ProjectileDefault::Update(float delta, GameManager* manager) {
	position.y += delta * direction.y * speed;

	if (position.y < 0.0f) {
		manager->Remove(this);
	}
}


Projectile* ProjectileDefault::CreateCopy() const {
	return new ProjectileDefault(this);
}