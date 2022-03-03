#ifndef GAME_H
#define GAME_H

#include "resource_manager.h"
#include "renderer.h"
#include "utility.h"
#include "time.h"
#include "entity.h"
#include "player.h"
#include "level.h"

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

	Renderer* renderer;

	Player* players;

	Level* levels;

	Game(const unsigned int w, const unsigned int h);
	~Game();

	void init();
	void processInput();
	void update();
	void render(GLFWwindow* window, const unsigned int screen_width, const unsigned int screen_height);
	void detectCollisions();
};

#endif