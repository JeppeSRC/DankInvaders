#version 100

attribute vec3 position;
attribute vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;


varying vec2 texCoord;

void main() {

	texCoord = texCoords;
	gl_Position = projection * model * vec4(position, 1);

}