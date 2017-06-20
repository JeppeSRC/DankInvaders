#version 100

precision mediump float;
precision mediump int;

varying vec2 texCoord;
varying vec4 color;
varying float tid;

uniform sampler2D samplers[32];

void main() {

	if (tid > -0.1) {
		gl_FragColor = texture2D(samplers[int(tid)], texCoord) * color;
	} else {
		gl_FragColor = color;
	}
}