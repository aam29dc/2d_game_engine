#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include "texture.h"

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

class Entity {
public:
	static unsigned int _count;

	glm::vec2 pos, size;
	glm::vec3 color;
	float angle;

	Texture2D* image;
	unsigned int frame;
	unsigned int cols;
	unsigned int rows;

	Entity(const unsigned int cols = 1, const unsigned int rows = 1);
	~Entity();

	void print() const {
		std::cout << "pos: " << pos.x << ", " << pos.y << "\n"
			<< "size: " << size.x << ", " << size.y << "\n"
			<< "color: " << color.x << ", " << color.y << color.z << "\n"
			<< "angle: " << angle << "\n"
			<< "frame: " << frame << "\n"
			<< "cols: " << cols << "\n"
			<< "rows: " << rows << "\n";
	}
};

#endif