#pragma once

#include "projectile.h"

class ProjectileDefault : public Projectile {
private:
	
public:
	ProjectileDefault(Ship* shooter, GameManager* manager);
	ProjectileDefault(const ProjectileDefault* other);

	//void Update(float delta, GameManager* manager) override;

	Projectile* CreateCopy() const override;
};
