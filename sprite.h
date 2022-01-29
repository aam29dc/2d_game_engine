#ifndef SPRITE_H
#define SPRITE_H

#include "shader.h"
#include "texture.h"
#include "object.h"
#include "time.h"
#include <glm/glm.hpp>

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

const unsigned int POINTS_SIZE = 8;
const unsigned int INDICES_SIZE = 6;
const unsigned int TC_SIZE = 8;

class Sprite {
public:
	unsigned int vao;
	Shader* shader;
	float lastTime;

	Sprite(Shader* shaderx);
	~Sprite();

	void calcTextureCoords(Object& animate, GLfloat (*tc)[TC_SIZE]);

	void initRenderData();
	void drawSprite(const Texture2D& texture, const glm::vec2 pos, const glm::vec2 size, const float rotate, const glm::vec3 color = glm::vec3(1,1,1));
	void drawText(Object& animate, const char* const text, const float offsetX, const float offsetY);
	void drawObject(Object& animate);
};

#endif