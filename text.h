#ifndef TEXT_H
#define TEXT_H

#include <glm/glm.hpp>
#include "texture.h"

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

class Text {
public:
	static unsigned int _count;

	glm::vec2 pos, size;
	glm::vec3 color;
	float angle;

	unsigned int frame;
	Texture2D* image;

	unsigned int cols;
	unsigned int rows;

	Text(const unsigned int cols = 1, const unsigned int rows = 1);
	~Text();
};

#endif