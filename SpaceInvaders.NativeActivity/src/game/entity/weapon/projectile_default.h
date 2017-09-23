#pragma once

#include "projectile.h"

class ProjectileDefault : public Projectile {
private:

public:
	ProjectileDefault(Ship* shooter);
	ProjectileDefault(const ProjectileDefault* other);
};
