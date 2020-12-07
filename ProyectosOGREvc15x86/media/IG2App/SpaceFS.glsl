#version 330 core


uniform sampler2D materialTex0;
uniform sampler2D materialTex1;

in vec2 vUv0;
in vec2 vUv1;


out vec4 fFragColor;

void main()
{
	vec3 m1  = vec3(texture(materialTex0, vUv0));
	vec3 m2  = vec3(texture(materialTex1, vUv1));
	fFragColor = vec4(m1*m2,1);
	//fFragColor = vec4(vec3(texture(materialTex0, vUv0) * vec3(texture(materialTex1, vUv1)), 1);
}
