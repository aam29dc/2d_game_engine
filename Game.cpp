#include "Game.h"

Sprite *renderer;
Object *someObject;

Game::Game(const unsigned int w, const unsigned int h) : State((GameState)0), _width(w), _height(h), currentTime((float)glfwGetTime()), deltaTime(currentTime), lastTime(0) {
}

Game::~Game() {
	delete renderer;
}

void Game::init() {
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/sprite.vs", "C:/Users/user052e/source/repos/glgui/glgui/sprite.fs");
	renderer = new Sprite(&ResourceManager::Shaders[0]);
	std::cout << "shader count: " << Shader::_count << "\n";

	ResourceManager::loadTexture("C:/game/textures/brick.jpg");
	ResourceManager::loadTexture("C:/game/textures/walk.png", true);
	ResourceManager::loadTexture("C:/game/textures/grid.jpg");
	std::cout << "texture count: " << Texture2D::_count << "\n";

	someObject = new Object(8*7, 8, 7);
	someObject->image = &ResourceManager::Textures[1];
	someObject->print();
}

void Game::processInput() {

}

void Game::update() {

}

float ct = 0, lt = 0, dt = 0;

void Game::render() {
	//renderer->drawSprite(ResourceManager::Textures[2], glm::vec2(0,0), glm::vec2(1, 1), 0.0f);

	ct = (float)glfwGetTime();
	dt = ct - lt;

	if (dt >= 0.5f) {
		if (someObject->frame >= someObject->maxFrames) someObject->frame = 0;
		lt = ct;
		someObject->frame++;
	}

	renderer->drawObject(*someObject);
}

void Game::calcTime() {
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}