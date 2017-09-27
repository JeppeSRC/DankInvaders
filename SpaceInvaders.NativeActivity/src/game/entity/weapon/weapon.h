#pragma once

#include <game/entity/projectiles/projectile.h>

enum WEAPON_TYPE {
	WEAPON_TYPE_UNKNOWN,
	WEPAON_TYPE_DEFAULT
};

class Weapon : public Entity {
private:
	WEAPON_TYPE type;
protected:
	float rateOfFire;

	Projectile* projectile;

	Weapon(Projectile* projectil, float rateOfFire, WEAPON_TYPE type, GameManager* manager);
public:
	virtual ~Weapon();

	virtual void Update(float delta) override = 0;

	inline float GetRateOfFire() const { return rateOfFire; }

	inline WEAPON_TYPE GetType() const { return type; }
};
