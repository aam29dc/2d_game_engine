#include "object.h"

Object::Object(const unsigned int width, const unsigned int height) :maxFrames(width* height), cell_w(width), cell_h(height) {
	pos = glm::vec2(0, 0);
	size = glm::vec2(1, 1);
	color = glm::vec3(1, 1, 1);
	angle = 0.0f;
	frame = 0;
	image = nullptr;
}

Object::~Object() {
}