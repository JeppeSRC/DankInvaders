#include "weapon_default.h"
#include <game/gamemanager.h>

WeaponDefault::WeaponDefault(Projectile* projectile, GameManager* manager) : Weapon(projectile, 10.0f, WEPAON_TYPE_DEFAULT, manager) {
	timer = 0;
}

void WeaponDefault::Update(float delta) {
	timer += rateOfFire * delta;
	
	if (timer >= 1.0f) {
		timer--;

		Projectile* p = projectile->CreateCopy();
		manager->Add(p);
	}
}