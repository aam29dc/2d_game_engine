#include "shader.h"
#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

unsigned int Shader::_count = 0;

//static unsigned int shader_invokes = 0;
Shader::Shader() : ID(-1) {
	//shader_invokes++;
	//std::cout << "Shader invokes: " << shader_invokes << ",\t";
}

Shader& Shader::Use() {
	glUseProgram(this->ID);
	return *this;
}

bool Shader::compile(const char* const vsource, const char* const fsource) {
	bool success = true;

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vsource, NULL);
	glCompileShader(vshader);
	success &= checkErrors(vshader);

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fsource, NULL);
	glCompileShader(fshader);
	success &= checkErrors(fshader);

	this->ID = 0;
	this->ID = glCreateProgram();
	std::cout << "shader id.x: " << this->ID << "\n";
	glAttachShader(this->ID, vshader);
	glAttachShader(this->ID, fshader);
	glLinkProgram(this->ID);
	success &= checkErrors(this->ID, "PROGRAM");

	_count++;

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	return success;
}

bool Shader::checkErrors(const unsigned int obj, const char* const type) const {
	int success;
	char infolog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(obj, 1024, NULL, infolog);
			std::cout << "ERROR: SHADER COMPILE_STATUS - \n" << infolog << "\n\n";
		}
	}
	else {
		glGetProgramiv(obj, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(obj, 1024, NULL, infolog);
			std::cout << "ERROR: PROGRAM LINK_STATUS - \n" << infolog << "\n\n";
		}
	}

	return success;
}

unsigned int Shader::getID() const {
	return this->ID;
}

void Shader::setMatrix4(const char* const name, const glm::mat4& matrix, const bool use) {
	if(use)
		this->Use();

	glUniformMatrix4fv(glGetUniformLocation(this->getID(), name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::setVec3f(const char* const name, const glm::vec3& vec, const bool use) {
	if (use)
		this->Use();

	glUniform3f(glGetUniformLocation(this->getID(), name), vec.x, vec.y, vec.z);
}