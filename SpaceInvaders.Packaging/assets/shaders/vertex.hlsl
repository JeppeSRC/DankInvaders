#version 100

attribute vec3 position;
attribute vec2 texCoords;
attribute vec4 colors;
attribute float tids;

uniform mat4 projection;

varying vec2 texCoord;
varying vec4 color;
varying float tid;

void main() {

	texCoord = texCoords;
	color = colors;
	tid = tids;
	gl_Position = projection * vec4(position, 1);

}