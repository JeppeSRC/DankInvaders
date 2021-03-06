#pragma once

#include "entity.h"
#include "weapon/weapon.h"

enum SHIP_TYPE {
	SHIP_TYPE_UNKNOWN,
	SHIP_TYPE_AISHIP,
	SHIP_TYPE_PLAYER
};

class Ship : public Entity {
private:
	SHIP_TYPE type;
protected:
	float health;
	float speed;

	Weapon* weapon;

	Ship(vec3 position, vec2 size, SHIP_TYPE type, GameManager* manager);
public:
	virtual ~Ship() {}

	virtual void Update(float delta) override = 0;
	virtual void OnHit(Projectile* projectil);

	inline float GetHealth() const { return health; }
	inline float GetSpeed() const { return speed; }

	inline SHIP_TYPE GetType() const { return type; }
};