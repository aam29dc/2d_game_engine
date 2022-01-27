#version 410

layout (location = 0) in vec2 p;
layout (location = 1) in vec2 tc;

out vec2 textcoords;

uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

void main() {
	gl_Position = projection*model*vec4(p, 0, 1);
	textcoords = tc;
}