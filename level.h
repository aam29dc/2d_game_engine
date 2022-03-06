#ifndef LEVEL_H
#define LEVEL_H

#include "game_object.h"
#include "utility.h"

const unsigned int MAP_SIZE = 400;

class Level {
public:
	GameObject* bricks;
	Texture2D* image;

	Level();
	~Level();

	void init(Texture2D* default_texture);
	void loadLevel(const char* const file);
};

#endif