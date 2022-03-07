#ifndef SPRITE_H
#define SPRITE_H

#include "shader.h"
#include "texture.h"
#include "entity.h"
#include "time.h"
#include "player.h"
#include "level.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

const unsigned int VERTICES_SIZE = 8;
const unsigned int INDICES_SIZE = 6;
const unsigned int TC_SIZE = 8;

class Renderer {
public:
	unsigned int vao;

	GLuint vbo_v;
	GLuint vbo_tc;
	GLuint vbo_i;
	GLuint ebo;
	GLuint ubo;

	Shader* shader;
	Shader* instance;

	Renderer(Shader& shader, Shader& instance);
	~Renderer();

	void calcTextureCoords(Entity& animate, GLfloat (*tc)[TC_SIZE]);

	void initRenderData();
	void drawQuad(const Texture2D& texture, const glm::vec2 pos = glm::vec2(0,0), const glm::vec2 size = glm::vec2(1,1), const float rotate = 0.0f, const glm::vec3 color = glm::vec3(1,1,1));
	void drawText(Entity& animate, const char* const text, const float offsetX, const float offsetY);
	void drawTime(Entity& animate, const float offsetX, const float offsetY, const unsigned int decimals);
	void drawFPS(Entity& animate, const float offsetX, const float offsetY);
	void drawEntity(Entity& animate, const bool sprite = false);
	void drawPlayer(Player& player);
	void drawCrosshair(GLFWwindow* window, const Texture2D& texture, const unsigned int screen_width, const unsigned int screen_height);
	//void drawHUD //text,timer,fps,crosshair,healthbar,inventory, ...
	void drawLevel(Level& lvl);
};

#endif