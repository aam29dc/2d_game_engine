#include "Game.h"

Sprite *renderer;

Game::Game(const unsigned int w, const unsigned int h) : State((GameState)0), _width(w), _height(h) {
}

Game::~Game() {
	delete renderer;
}

void Game::init() {
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/sprite.vs", "C:/Users/user052e/source/repos/glgui/glgui/sprite.fs");
	renderer = new Sprite(&ResourceManager::Shaders[0]);
	std::cout << "shader count: " << Shader::_count << "\n";

	ResourceManager::loadTexture("C:/game/textures/brick.jpg");
	std::cout << "texture count: " << Texture2D::_count << "\n";
}

void Game::processInput() {

}

void Game::update() {

}

void Game::render() {
	glm::vec2 pos = glm::vec2(0, 0);
	glm::vec2 size = glm::vec2(1, 1);
	renderer->drawSprite(ResourceManager::Textures[0], pos, size, 30.0f);
}