#version 100

precision mediump float;
precision mediump int;

varying vec2 texCoord;
varying vec4 color;
varying float tid;

uniform sampler2D samplers[16];

void main() {

	vec4 tex = color;
	
	if (tid > -0.1) {
		tex *= texture2D(samplers[int(tid)], texCoord);
	}

	gl_FragColor = tex;
}