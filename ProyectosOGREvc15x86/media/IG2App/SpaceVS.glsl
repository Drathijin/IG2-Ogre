#version 330 core


uniform mat4 modelViewProjMat;
uniform float SinTiempo;

in vec4 vertex;
in vec2 uv0;


out vec2 vUv0;
out vec2 vUv1;

void main()
{
	//float ZF = 0.5;
	float ZF = (SinTiempo + 1) /4 + 0.5;
	vUv0 = uv0;

	vec2 uv1 = ((uv0 - 0.5) * ZF + 0.5);
	vUv1 = uv1;

	gl_Position = modelViewProjMat * vertex;
}