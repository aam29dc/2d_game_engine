#include "Game.h"

const float TEXT_SIZE = 0.025f;
const float TEXT_SMALL = TEXT_SIZE / 2.0f;
const float TEXT_LARGE = 2.0f * TEXT_SIZE;

Game::Game(const unsigned int w, const unsigned int h) : State((GameState)0), _width(w), _height(h), text(Entity(16,16)) {
}

Game::~Game() {
	delete Game::renderer;
	delete[] Game::entities;
	delete[] Game::objects;
	delete[] Game::levels;
	delete[] Game::players;
}

void Game::init() {
	ResourceManager::Shaders = new Shader[2];
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/sprite.vs", "C:/Users/user052e/source/repos/glgui/glgui/sprite.fs");
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/instance.vs", "C:/Users/user052e/source/repos/glgui/glgui/instance.fs");
	std::cout << "shader count: " << Shader::_count << "\n";

	Game::renderer = new Renderer(ResourceManager::Shaders[0], ResourceManager::Shaders[1]);

	ResourceManager::Textures = new Texture2D[4];
	ResourceManager::loadTexture("C:/game/textures/atlas.jpg");
	ResourceManager::loadTexture("C:/game/textures/walk.png", true);
	ResourceManager::loadTexture("C:/game/textures/font3.png", true);
	ResourceManager::loadTexture("C:/game/textures/xhair.png", true);
	ResourceManager::loadTexture("C:/game/textures/brick.jpg");
	std::cout << "texture count: " << Texture2D::_count << "\n";

	Game::players = new Player[1];
	Game::players[0].angle = 0;
	Game::players[0].frame = 0;
	Game::players[0].cols = 8;
	Game::players[0].rows = 8;
	Game::players[0].image = &ResourceManager::Textures[1];
	Game::players[0].size = glm::vec2(0.25, 0.25);
	Game::players[0].color = glm::vec3(1.0f, 1.0f, 0.0f);
	Game::players[0].pos = glm::vec2(-0.5, -0.5);
	Game::players[0].dir = d;

	Game::text.color = glm::vec3(0, 1, 0);
	Game::text.size = glm::vec2(TEXT_SIZE, TEXT_SIZE);
	Game::text.image = &ResourceManager::Textures[2];

	Game::levels = new Level[1];
	levels[0].init(ResourceManager::Textures[0]);

	Game::objects = new GameObject[1];
	objects[0].pos = glm::vec2(0.0, 0.0);
	objects[0].size = glm::vec2(0.25, 0.25);
	objects[0].angle = 0.0f;
	objects[0].frame = 0;
	objects[0].destroyed = false;
	objects[0].image = &ResourceManager::Textures[4];
	objects[0].solid = true;
	objects[0].rows = 1;
	objects[0].cols = 1;
}

void Game::processInput() {
	Game::players[0].calcDirection(&_keys);
}

void Game::update() {
	//detectCollisions();
	double speed = 0.6 * (double)Time::delta;

	/*	player directions:
		w = 0, s = 1, a = 2, d = 3
	*/

	if (Game::_keys[GLFW_KEY_W])
	{
		if (Game::players[0].pos.y <= 1.0 - Game::players[0].size.y / 2.0)
		{
			if (!checkCollisions(Game::players[0], 0)) {
				Game::players[0].pos.y += (float)speed;
			}
		}
	}
	if (Game::_keys[GLFW_KEY_S])
	{
		if (Game::players[0].pos.y >= -0.9 + Game::players[0].size.y / 2.0)		//1 to 0.9 to adjust for image height and center
		{
			if (!checkCollisions(Game::players[0], 1)) {
				Game::players[0].pos.y -= (float)speed;
			}
		}
	}
	if (Game::_keys[GLFW_KEY_A])
	{
		if (Game::players[0].pos.x >= -1.0 + Game::players[0].size.x / 2.0)
		{
			if (!checkCollisions(Game::players[0], 2)) {
				Game::players[0].pos.x -= (float)speed;
			}
		}
	}
	if (Game::_keys[GLFW_KEY_D])
	{
		if (Game::players[0].pos.x <= 1.0 - Game::players[0].size.x / 2.0)
		{
			if (!checkCollisions(Game::players[0], 3)) {
				Game::players[0].pos.x += (float)speed;
			}
		}
	}
}

void Game::render(GLFWwindow* window, const unsigned int screen_width, const unsigned int screen_height) {
	//Game::renderer->drawQuad(ResourceManager::Textures[0]);		//background
	Game::renderer->drawLevel(Game::levels[0]);

	for (unsigned int i = 0; i < 1; i++) {
		Game::renderer->drawEntity(objects[i]);
	}

	for (unsigned int i = 0; i < Game::players->_count; i++) {
		Game::renderer->drawPlayer(players[i]);
	}

	Game::renderer->drawTime(text, 1, 0.8f, 1);

	Game::renderer->drawText(text, "Hello circus clown, no questions allowed! Goats are not the meta.", 0, 0);
	Game::renderer->drawText(text, "This is another run on sentence or I dont know what im talking about?", 0, 0.2f);

	Game::renderer->drawFPS(text, 0, .9f);

	Game::renderer->drawCrosshair(window, ResourceManager::Textures[3], screen_width, screen_height);
}

bool Game::checkCollisions(Player& player, const unsigned int dir) {
	double y_speed = 0.0;
	double x_speed = 0.0;

	if (dir == 0) {			// w
		y_speed = 0.6 * (float)Time::delta;
	}
	else if (dir == 1) {	//s
		y_speed = -0.6 * (float)Time::delta;
	}
	else if (dir == 2) {	//a
		x_speed = -0.6 * (float)Time::delta;
	}
	else {					//d
		x_speed = 0.6 * (float)Time::delta;
	}

	for (unsigned int j = 0; j < 1; j++) {
		if (Game::objects[j].solid) {
			if (player.pos.x + x_speed >= Game::objects[j].pos.x - (Game::objects[j].size.x * 1.1) &&
				player.pos.x + x_speed <= Game::objects[j].pos.x + (Game::objects[j].size.x * 1.1) &&
				player.pos.y + y_speed >= Game::objects[j].pos.y - (Game::objects[j].size.y / 1.5) &&
				player.pos.y + y_speed <= Game::objects[j].pos.y + (Game::objects[j].size.y * 1.6)) {
					//Game::objects[j].solid = false;
					//Game::objects[j].destroyed = true;
					return true;
			}
		}
	}
	return false;
}

/*
void Game::detectCollisions() {
	//check collisions of players against other players
	for (unsigned int i = 0; i < Player::_count; i++) {
		for (unsigned int j = i+1; j < Player::_count; j++) {
	
		}
	}

	//check collisions of players against other lvl entities
	for (unsigned int i = 0; i < Player::_count; i++) {
		for (unsigned int j = 0; j < MAP_SIZE; j++) {
			if (Game::levels[0].bricks[j].solid) {
				if (Game::players[i].pos.x >= Game::levels[0].bricks[j].pos.x &&
					Game::players[i].pos.x <= Game::levels[0].bricks[j].pos.x + Game::levels[0].bricks[j].size.x / 2.0f &&
					Game::players[i].pos.y >= Game::levels[0].bricks[j].pos.y &&
					Game::players[i].pos.y <= Game::levels[0].bricks[j].pos.y + Game::levels[0].bricks[j].size.y / 2.0f) {
						Game::players[i].speed = 0.0f;
						std::cout << "coll lvl\n";
				}
			}
		}
	}

	//check collisions of players against game objects
	for (unsigned int i = 0; i < Player::_count; i++) {
		for (unsigned int j = 0; j < 1; j++) {
			if (Game::objects[j].solid) {
				if (Game::players[i].pos.x >= Game::objects[j].pos.x &&
					Game::players[i].pos.x <= Game::objects[j].pos.x + Game::objects[j].size.x / 2.0f &&
					Game::players[i].pos.y >= Game::objects[j].pos.y &&
					Game::players[i].pos.y <= Game::objects[j].pos.y + Game::objects[j].size.y / 2.0f) {
						Game::players[i].speed = 0.0f;
						//Game::entities[j].solid = false;
						//Game::entities[j].destroyed = true;
						std::cout << "coll e\n";
				}
				else Game::players[i].speed = 0.6f;
			}
		}
	}
}*/