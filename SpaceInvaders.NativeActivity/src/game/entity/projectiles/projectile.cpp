#include "projectile.h"
#include <game/entity/ship.h>

Projectile::Projectile(vec3 position, vec2 size, Ship* shooter, PROJECTILE_TYPE type) : Entity(position, size, ENTITY_TYPE_PROJECTILE), type(type), shooter(shooter) {

}

Projectile::Projectile(const Projectile* other) : Entity(other->shooter->GetPosition(), other->size, ENTITY_TYPE_PROJECTILE), type(other->type), damage(other->damage), speed(other->speed), direction(other->direction), shooter(other->shooter) {

}