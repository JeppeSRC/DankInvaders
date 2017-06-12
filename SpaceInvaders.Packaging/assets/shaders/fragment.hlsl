#version 100

precision highp float;

varying vec2 texCoord;

uniform sampler2D sampler;

void main() {

	vec4 color = texture2D(sampler, texCoord.xy);


	if (color.a > 0.0)
		gl_FragColor = vec4(color.xy, 1, 1);
	else
		gl_FragColor = vec4(1, 0, 1, 1);

}