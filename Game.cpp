#include "Game.h"

Sprite *renderer;
Object *someObject;
Object* text;

Game::Game(const unsigned int w, const unsigned int h) : State((GameState)0), _width(w), _height(h) {
}

Game::~Game() {
	delete renderer;
}

const float TEXT_SIZE = 0.025f;
const float TEXT_SMALL = TEXT_SIZE/2.0f;
const float TEXT_LARGE = 2.0f*TEXT_SIZE;

void Game::init() {
	ResourceManager::loadShader("C:/Users/user052e/source/repos/glgui/glgui/sprite.vs", "C:/Users/user052e/source/repos/glgui/glgui/sprite.fs");
	renderer = new Sprite(&ResourceManager::Shaders[0]);
	std::cout << "shader count: " << Shader::_count << "\n";

	ResourceManager::loadTexture("C:/game/textures/brick.jpg");
	ResourceManager::loadTexture("C:/game/textures/walk.png", true);
	ResourceManager::loadTexture("C:/game/textures/grid.jpg");
	ResourceManager::loadTexture("C:/game/textures/font3.png", true);
	std::cout << "texture count: " << Texture2D::_count << "\n";

	someObject = new Object(8, 8);
	someObject->image = &ResourceManager::Textures[1];
	someObject->print();

	text = new Object(16, 16);
	text->angle = 0;
	text->color = glm::vec3(0, 1, 0);
	text->size = glm::vec2(TEXT_SIZE, TEXT_SIZE);
	text->image = &ResourceManager::Textures[3];
}

void Game::processInput() {

}

void Game::update() {

}

void Game::render() {
	//renderer->drawSprite(ResourceManager::Textures[2], glm::vec2(0,0), glm::vec2(1, 1), 0.0f);

	/*
	ct = (float)glfwGetTime();
    dt = ct - lt;

    if (dt >= 0.5f) {
        std::cout << ct << " " << dt << " " << lt <<  " " << animate.frame << "\n";
        if (animate.frame >= animate.maxFrames) animate.frame = 0;
        lt = ct;
        animate.frame++;
    }
	*/

	renderer->drawObject(*someObject);
	renderer->drawText(*text, "Hello circus clown, do you know? How do you know that? ... I? Me either. HaHaHaHa", 0, 0);
}