#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "texture.h"

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

class Object {
public:
	glm::vec2 pos, size;
	glm::vec3 color;
	float angle;

	Texture2D* image;
	unsigned int frame;
	const unsigned int maxFrames;
	const unsigned int cell_w;
	const unsigned int cell_h;

	Object(const unsigned int width, const unsigned int height);
	~Object();

	void print() const {
		std::cout << "pos: " << pos.x << ", " << pos.y << "\n"
		<< "size: " << size.x << ", " << size.y << "\n"
		<< "color: " << color.x << ", " << color.y << color.z << "\n"
		<< "angle: " << angle << "\n"
		<< "frame: " << frame << "\n"
		<< "maxFrames: " << maxFrames << "\n"
		<< "cell_w: " << cell_w << "\n"
		<< "cell_h: " << cell_h << "\n"
		<< "cell_h: " << cell_h << "\n";
	}
};

#endif