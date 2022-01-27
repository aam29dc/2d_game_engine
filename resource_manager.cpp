#include "resource_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader ResourceManager::Shaders[MAX_SHADERS];
Texture2D ResourceManager::Textures[MAX_TEXTURES];

void ResourceManager::clear() {
	for (unsigned int i = 0; i < Shader::_count - 1; i++) {
		glDeleteProgram(Shaders[i].getID());
	}

	Shader::_count = 0;

	for (unsigned int i = 0; i < Texture2D::_count - 1; i++) {
		glDeleteTextures(1, &(Textures[i].ID));
	}

	Texture2D::_count = 0;
}

void ResourceManager::loadShader(const char* const vsFile, const char* const fsFile) {
	Shader shader;
	std::string vs = Utility::getFileData(vsFile);
	std::string fs = Utility::getFileData(fsFile);

	const char* cvs = vs.c_str();
	const char* cfs = fs.c_str();

	shader.ID = 0;

	shader.compile(cvs, cfs);	//_count ++
	Shaders[Shader::_count - 1] = shader;
}

/*Shader& ResourceManager::getShader(unsigned int index) {
	return ResourceManager::Shaders[index];
}*/

void ResourceManager::loadTexture(const char* const file, const bool alpha) {
	Texture2D texture;

	if (alpha) {
		texture.image_format = GL_RGBA;
		texture.internal_format = GL_RGBA;
	}

	int w = 0, h = 0, nrC = 0;
	unsigned char* data = stbi_load(file, &w, &h, &nrC, 0);
	if (data) {
		texture.generate(w, h, data);
	}
	stbi_image_free(data);

	Textures[Texture2D::_count - 1] = texture;
}

/*Texture2D& ResourceManager::getTexture(const unsigned int index) {
	if (index <= Texture2D::_count) {
		return ResourceManager::Textures[index];
	}
	...
}
*/