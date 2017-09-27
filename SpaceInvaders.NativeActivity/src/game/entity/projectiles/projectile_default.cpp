#include "projectile_default.h"
#include <game/entity/ship.h>
#include <game/gamemanager.h>

ProjectileDefault::ProjectileDefault(Ship* shooter, GameManager* manager) : Projectile(shooter->GetPosition() - shooter->GetSize().y + size.y / 2.0f, vec2(20, 20), shooter, PROJECTILE_TYPE_DEFAULT, manager) {
	damage = 1.0f;
	speed = 500.0f;

	direction = vec2(0, -1);
}

ProjectileDefault::ProjectileDefault(const ProjectileDefault* other) : Projectile(other) {

}


Projectile* ProjectileDefault::CreateCopy() const {
	return new ProjectileDefault(this);
}