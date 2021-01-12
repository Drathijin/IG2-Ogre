#version 330 core // archivo LuminancePS.glsl
in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
uniform float kernel[9];
out vec4 fFragColor;
const float OFFSET = 10;

void main() {

	ivec2 texSize = textureSize(RTT0,0);
	float incS = 1. / float(texSize.s);
	float incT = 1. / float(texSize.t);
	vec2 incUV[9] = vec2[](
		vec2(-incS,incT),
		vec2(0,incT),
		vec2(incS,incT),
		vec2(-incS,0),
		vec2(0,0),
		vec2(incS,0),
		vec2(-incS,-incT),
		vec2(0,-incT),
		vec2(incS,-incT)
	);


	vec4 color = vec4(0);

	for(int i = 0; i <9; i++){
		vec2 desp = vUv0 + incUV[i];
		vec4 textDesp = texture(RTT0, desp);
		color+= texture(RTT0, vUv0+incUV[i]) * kernel[i];
	}

	fFragColor = color;
}