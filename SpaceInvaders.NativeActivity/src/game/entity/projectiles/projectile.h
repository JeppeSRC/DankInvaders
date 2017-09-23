#pragma once

#include <game/entity/entity.h>

enum PROJECTILE_TYPE {
	PROJECTILE_TYPE_UNKNOWN,
	PROJECTILE_TYPE_DEFAULT,
	PROJECTILE_TYPE_BULLET,
	PROJECTILE_TYPE_ROCKET
};

class Ship;

class Projectile : public Entity {
private:
	PROJECTILE_TYPE type;
protected:
	float damage;
	float speed;
	vec2 direction;

	Ship* shooter;

	Projectile(vec3 position, vec2 size, Ship* shooter, PROJECTILE_TYPE type);
	Projectile(const Projectile* other);
public:
	virtual ~Projectile() {}

	virtual void Update(float delta, GameManager* manager) override = 0;

	virtual Projectile* CreateCopy() const = 0;

	inline float GetDamage() const { return damage; }
	inline float GetSpeed() const { return speed; }
	inline vec2 GetDirection() const { return direction; }

	inline PROJECTILE_TYPE GetType() const { return type; }
};
