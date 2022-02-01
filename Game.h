#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "renderer.h"
#include "utility.h"
#include "time.h"
#include "entity.h"
#include "player.h"

enum GameState {
	MENU = 0,
	INGAME,
	END,
};

class Game {
public:
	GameState State;

	unsigned int _width, _height;

	bool _keys[1024] = { 0 };
	Entity text;

	Entity* entities;
	unsigned int entity_count;

	Renderer* renderer;

	Player* players;

	Game(const unsigned int w, const unsigned int h);
	~Game();

	void init();
	void processInput();
	void update();
	void render();
};

#endif