#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <GLFW/glfw3.h>

enum Dir {
		a = 0,
	wa = 1,
		w = 2,
	wd = 3,
		d = 4,
	sd = 5,
		s = 6,
	sa = 7,
};

class Player : public Entity {
public:
	static unsigned int _count;
	glm::vec2 velocity;
	unsigned int dir;
	bool still;			// stationary, not moving

	Player();
	~Player();
	void calcDirection(const bool(* const keys)[1024]);
};

#endif