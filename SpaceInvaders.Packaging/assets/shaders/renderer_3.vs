#version 300 es

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec4 colors;
layout(location = 3) in float tids;
layout(location = 4) in float texts;

out vec2 texCoord;
out vec4 color;
out float tid;
out float text;

uniform mat4 projection;

void main() {

	texCoord = texCoords;
	color = colors;
	tid = tids;
	text = texts;

	gl_Position = projection * vec4(positions, 1);
}
