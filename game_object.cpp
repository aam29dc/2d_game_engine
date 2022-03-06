#include "game_object.h"

unsigned int GameObject::_count = 0;

GameObject::GameObject(const unsigned int width, const unsigned int height) {
	cols = width;
	rows = height;
	pos = glm::vec2(0, 0);
	size = glm::vec2(1, 1);
	color = glm::vec3(1, 1, 1);
	angle = 0.0f;
	frame = 0;
	frameTime = 0.0f;
	image = nullptr;
	solid = false;
	destroyed = false;
	_count++;
}

GameObject::~GameObject() {
	_count--;
}