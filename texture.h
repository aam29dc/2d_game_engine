#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <iostream>

class Texture2D {
private:
public:
	unsigned int ID;
	static unsigned int _count;

	unsigned int height, width;
	unsigned int internal_format, image_format;
	unsigned int wrap_s, wrap_t;
	unsigned int filter_min, filter_mag;

	Texture2D();
	void generate(const unsigned int w, const unsigned int h, const unsigned char* const data);
	void bind() const;
};

#endif