#include "weapon_default.h"
#include <game/gamemanager.h>

WeaponDefault::WeaponDefault(Projectile* projectile) : Weapon(projectile, 5.0f, WEPAON_TYPE_DEFAULT) {
	timer = 0;
}

void WeaponDefault::Update(float delta, GameManager* manager) {
	timer += rateOfFire * delta;
	
	if (timer >= 1.0f) {
		timer--;

		Projectile* p = projectile->CreateCopy();
		manager->Add(p);
	}
}