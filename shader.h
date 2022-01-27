#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	static unsigned int _count;
	unsigned int ID;

	Shader();
	Shader& Use();
	bool compile(const char* const vsource, const char* const fsource);
	bool checkErrors(const unsigned int obj, const char* const type = "SHADER") const;
	unsigned int getID() const;

	void setMatrix4(const char* const name, const glm::mat4 &matrix, const bool use = false);
	void setVec3f(const char* const name, const glm::vec3 &vec, const bool use = false);
};

#endif