#include "texture.h"

unsigned int Texture2D::_count = 0;

//static unsigned int texture_invokes = 0;
Texture2D::Texture2D() : ID(-1), height(0), width(0), internal_format(GL_RGB), image_format(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filter_min(GL_LINEAR), filter_mag(GL_LINEAR) {
	//texture_invokes++;
	//std::cout << "Texture 2d invoked: " << texture_invokes << ",\t";
}

void Texture2D::generate(const unsigned int w, const unsigned int h, const unsigned char* const data) {
	this->ID = 0;
	glGenTextures(1, &this->ID);

	std::cout << "texture id: " << this->ID << "\n";

	this->width = w;
	this->height = h;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_mag);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, this->width, this->height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

	_count++;
}
void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}