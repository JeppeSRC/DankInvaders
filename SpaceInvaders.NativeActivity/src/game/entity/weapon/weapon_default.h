#pragma once

#include "weapon.h"

class WeaponDefault : public Weapon {
private:
	float timer;
public:
	WeaponDefault(Projectile* projectile);

	void Update(float delta, GameManager* manager) override;
};
