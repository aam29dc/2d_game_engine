#include "Game.h"

const float TEXT_SIZE = 0.025f;
const float TEXT_SMALL = TEXT_SIZE / 2.0f;
const float TEXT_LARGE = 2.0f * TEXT_SIZE;

Game::Game(const unsigned int w, const unsigned int h) : State((GameState)0), _width(w), _height(h), text(Entity(16,16)), entity_count(0) {
}

Game::~Game() {
	delete Game::renderer;
	delete [] Game::entities;
}

void Game::init() {
	ResourceManager::Shaders = new Shader[1];
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/sprite.vs", "C:/Users/user052e/source/repos/glgui/glgui/sprite.fs");
	std::cout << "shader count: " << Shader::_count << "\n";

	Game::renderer = new Renderer(&ResourceManager::Shaders[0]);

	ResourceManager::Textures = new Texture2D[3];
	ResourceManager::loadTexture("C:/game/textures/brick.jpg");
	ResourceManager::loadTexture("C:/game/textures/walk.png", true);
	ResourceManager::loadTexture("C:/game/textures/font3.png", true);
	std::cout << "texture count: " << Texture2D::_count << "\n";

	Game::players = new Player[1];
	Game::players[0].angle = 0;
	Game::players[0].frame = 0;
	Game::players[0].cols = 8;
	Game::players[0].rows = 8;
	Game::players[0].image = &ResourceManager::Textures[1];
	Game::players[0].size = glm::vec2(0.25f, 0.25f);
	Game::players[0].color = glm::vec3(1.0f, 1.0f, 0.0f);
	Game::players[0].pos = glm::vec2(0, -0.5);
	Game::players[0].dir = d;

	Game::text.color = glm::vec3(0, 1, 0);
	Game::text.size = glm::vec2(TEXT_SIZE, TEXT_SIZE);
	Game::text.image = &ResourceManager::Textures[2];
}

void Game::processInput() {
	float velocity = 0.6f * Time::delta;

	if (Game::_keys[GLFW_KEY_W])
	{
		if (Game::players[0].pos.y <= 1.0f - Game::players[0].size.y/2.0f)
		{
			Game::players[0].pos.y += velocity;
		}
	}
	if (Game::_keys[GLFW_KEY_S])
	{
		if (Game::players[0].pos.y >= -0.9f + Game::players[0].size.y/2.0f)		//1 to 0.9 to adjust for image height and center
		{
			Game::players[0].pos.y -= velocity;
		}
	}
	if (Game::_keys[GLFW_KEY_A])
	{
		if (Game::players[0].pos.x >= -1.0f + Game::players[0].size.x/2.0f)
		{
			Game::players[0].pos.x -= velocity;
		}
	}
	if (Game::_keys[GLFW_KEY_D])
	{
		if (Game::players[0].pos.x <= 1.0f - Game::players[0].size.x/2.0f)
		{
			Game::players[0].pos.x += velocity;
		}
	}

	Game::players[0].calcDirection(&_keys);
}

void Game::update() {

}

void Game::render() {
	Game::renderer->drawQuad(ResourceManager::Textures[0]);		//background

	for (unsigned int i = 0; i < Game::entity_count; i++) {
		Game::renderer->drawEntity(entities[i]);
	}

	for (unsigned int i = 0; i < Game::players->_count; i++) {
		Game::renderer->drawPlayer(players[i]);
	}

	Game::renderer->drawText(text, "Hello circus clown, no questions allowed! Goats are not the meta.", 0, 0);
	Game::renderer->drawText(text, "This is another run on sentence or I dont know what im talking about?", 0, 0.2f);
}