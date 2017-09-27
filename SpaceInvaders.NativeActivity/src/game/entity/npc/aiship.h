#pragma once

#include <game/entity/ship.h>

enum AISHIP_TYPE {
	AISHIP_TYPE_UNKNOWN,
	AISHIP_TYPE_DEFAULT
};

class AIShip : public Ship {
private:
	AISHIP_TYPE type;
protected:
	
	AIShip(vec3 position, vec2 size, AISHIP_TYPE type, GameManager* manager);
public:
	virtual ~AIShip();

	virtual void Update(float delta) override = 0;

	inline AISHIP_TYPE GetType() const { return type; }
};
