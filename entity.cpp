#include "entity.h"

unsigned int Entity::_count = 0;

Entity::Entity(const unsigned int width, const unsigned int height) : cols(width), rows(height) {
	pos = glm::vec2(0, 0);
	size = glm::vec2(1, 1);
	color = glm::vec3(1, 1, 1);
	angle = 0.0f;
	frame = 0;
	image = nullptr;

	_count++;
}

Entity::~Entity() {
	_count--;
}