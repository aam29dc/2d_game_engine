#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
	static unsigned int _count;
	glm::vec2 velocity;
	Player();
	~Player();
};

#endif