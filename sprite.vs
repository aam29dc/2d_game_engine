#version 330

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 tc;

out vec2 textcoords;

layout (std140) uniform CONST_DATA {
	mat4 projection;
};
uniform mat4 model;
uniform vec3 color;

void main() {
	gl_Position = projection*model*vec4(vertex, 0, 1);
	textcoords = tc;
}