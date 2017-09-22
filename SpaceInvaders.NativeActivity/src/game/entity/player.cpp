#include "player.h"

Player::Player(vec3 position) : Entity(position, vec2(50, 50)) {
	color = vec4(1, 1, 0, 1);
}

void Player::Update(float delta, vec2 input) {

}