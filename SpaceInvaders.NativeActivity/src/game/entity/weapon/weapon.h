#pragma once

#include "projectile.h"

enum WEAPON_TYPE {
	WEAPON_TYPE_UNKNOWN,
	WEPAON_TYPE_DEFAULT
};

class Weapon : public Entity {
private:
	WEAPON_TYPE type;
protected:
	float rateOfFire;

	Weapon(float rateOfFire);
public:
	virtual ~Weapon();

	virtual void Update(float delta, vec2 input) override = 0;

	inline float GetRateOfFire() const { return rateOfFire; }

	inline WEAPON_TYPE GetType() const { return type; }
};
