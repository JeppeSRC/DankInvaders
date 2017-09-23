#include "weapon.h"

Weapon::Weapon(float rateOfFire) : Entity(vec3(0, 0, 0), vec2(0, 0), ENTITY_TYPE_WEAPON), rateOfFire(rateOfFire) {

}

Weapon::~Weapon() {

}

void Weapon::Update(float delta, vec2 input) {

}