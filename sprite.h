#ifndef SPRITE_H
#define SPRITE_H

#include "shader.h"
#include "texture.h"
#include <glm/glm.hpp>

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

class Sprite {
public:
	unsigned int vao;
	Shader* shader;

	Sprite(Shader* shaderx);
	~Sprite();

	void initRenderData();
	void drawSprite(const Texture2D& texture, const glm::vec2 pos, const glm::vec2 size, const float rotate, const glm::vec3 color = glm::vec3(1,1,1));
private:

};

#endif