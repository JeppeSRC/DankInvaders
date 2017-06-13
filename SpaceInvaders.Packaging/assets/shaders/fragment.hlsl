#version 100

precision highp float;
precision highp int;

varying vec2 texCoord;
varying vec4 color;
varying float tid;

uniform sampler2D sampler[32];

void main() {

	highp int t = int(tid);
	gl_FragColor = texture2D(sampler[t], texCoord);
}