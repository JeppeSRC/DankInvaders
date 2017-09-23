#include "weapon.h"
#include <game/gamemanager.h>

Weapon::Weapon(Projectile* projectile, float rateOfFire, WEAPON_TYPE type) : Entity(vec3(0, 0, 0), vec2(0, 0), ENTITY_TYPE_WEAPON), type(type), rateOfFire(rateOfFire), projectile(projectile) {

}

Weapon::~Weapon() {

}

