#version 100

attribute vec3 positions;
attribute vec2 texCoords;
attribute vec4 colors;
attribute float tids;

varying vec2 texCoord;
varying vec4 color;
varying float tid;

uniform mat4 projection;

void main() {

	texCoord = texCoords;
	color = colors;
	tid = tids;

	gl_Position = projection * vec4(positions, 1);
}
