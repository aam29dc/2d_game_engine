#version 410

in vec2 textcoords;
out vec4 frag;

uniform sampler2D image;

void main() {
	frag = vec4(1,1,1,1)*texture(image, textcoords);
}