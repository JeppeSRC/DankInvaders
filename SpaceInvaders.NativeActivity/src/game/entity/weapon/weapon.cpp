#include "weapon.h"
#include <game/gamemanager.h>

Weapon::Weapon(Projectile* projectile, float rateOfFire, WEAPON_TYPE type, GameManager* manager) : Entity(vec3(0, 0, 0), vec2(0, 0), ENTITY_TYPE_WEAPON, manager), type(type), rateOfFire(rateOfFire), projectile(projectile) {

}

Weapon::~Weapon() {

}

