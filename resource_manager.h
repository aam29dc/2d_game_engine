#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "shader.h"
#include "texture.h"
#include "utility.h"

const unsigned int MAX_SHADERS = 32;
const unsigned int MAX_TEXTURES = 32;

class ResourceManager {
public:
	static Shader Shaders[MAX_SHADERS];
	static Texture2D Textures[MAX_TEXTURES];

	static void clear();
	static void loadShader(const char* const vsFile, const char* const fsFile);
	//static Shader& getShader(const unsigned int ID);
	static void loadTexture(const char* const file, const bool alpha = false);
	//static Texture2D& getTexture(const unsigned int ID);
private:
	ResourceManager() {}
};

#endif
