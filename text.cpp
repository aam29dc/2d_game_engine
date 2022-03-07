#include "text.h"

Text::Text(const unsigned int width, const unsigned int height) : cols(width), rows(height) {
	pos = glm::vec2(0, 0);
	size = glm::vec2(1, 1);
	color = glm::vec3(1, 1, 1);
	angle = 0.0f;
	frame = 0;
	image = nullptr;
	_count++;
}

Text::~Text() {
	_count++;
}