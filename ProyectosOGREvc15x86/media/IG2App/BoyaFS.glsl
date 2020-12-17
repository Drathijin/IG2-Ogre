#version 330 core


uniform sampler2D materialTex0;
uniform sampler2D materialTex1;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

//uniform vec3 materialDiffuse;
uniform vec4 InColor;
uniform vec4 OutColor; 

in vec2 vUv0;
in vec3 vVertex;
in vec3 vNormal;
in vec3 amb1;
in vec3 amb2;


out vec4 fFragColor;


float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz;

	if(lightPosition.w == 1)
		lightDir = lightPosition.xyz - cVertex;

	return max(dot(cNormal, normalize(lightDir)), 0);
}


void main()
{

	vec3 diffuse = diff(vVertex, vNormal) * lightDiffuse;
	vec3 inColor = amb1 + diffuse;
	
	diffuse = diff(vVertex, -vNormal) * lightDiffuse;
	vec3 outColor = amb2 + diffuse;


	vec3 m1  = vec3(texture(materialTex0, vUv0));
	if(m1.r >= 0.5)
		discard;
	
	vec3 m2  = vec3(texture(materialTex1, vUv0));
	
	if(gl_FrontFacing)
		m1 = vec3(outColor);
	else 
		m1 = vec3(inColor);
	
	fFragColor = vec4(m1*m2,1);
}
