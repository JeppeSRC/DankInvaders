#version 100

varying vec2 texCoord;
varying vec4 color;
varying float tid;

uniform sampler2D samplers[32];

void main() {

	vec4 tex = vec4(1, 1, 1, 1);

	if (tid > -0.1)
		tex = texture2D(samplers[int(tid)], texCoord);

	gl_FragColor = color * tex;
}