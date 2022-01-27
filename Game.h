#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "sprite.h"
#include "utility.h"

enum GameState {
	MENU = 0,
	INGAME,
	END,
};

class Game {
public:
	GameState State;
	int _width, _height;
	char _keys[100] = { 0 };

	Game(const unsigned int w, const unsigned int h);
	~Game();

	void init();
	void processInput();
	void update();
	void render();
};

#endif