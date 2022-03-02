#version 410

layout (location = 0) in vec2 p;
layout (location = 1) in vec2 tc;

layout (location = 2) in vec4 m1;
layout (location = 3) in vec4 m2;
layout (location = 4) in vec4 m3;
layout (location = 5) in vec4 m4;

//layout (location = 3) in vec3 color;

out vec2 textcoords;

uniform mat4 projection;

void main() {
	mat4 model = mat4(m1,m2,m3,m4);
	gl_Position = projection*model*vec4(p, 0, 1);
	textcoords = tc;
}