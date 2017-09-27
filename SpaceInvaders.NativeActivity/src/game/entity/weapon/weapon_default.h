#pragma once

#include "weapon.h"

class WeaponDefault : public Weapon {
private:
	float timer;
public:
	WeaponDefault(Projectile* projectile, GameManager* manager);

	void Update(float delta) override;
};
