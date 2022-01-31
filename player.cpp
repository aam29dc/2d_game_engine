#include "player.h"

unsigned int Player::_count = 0;

Player::Player() : Entity(0,0), velocity(0.0f,0.0f) {
	_count++;
}

Player::~Player() {
	--_count;
}