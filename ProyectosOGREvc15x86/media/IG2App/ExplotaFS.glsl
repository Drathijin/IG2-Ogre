#version 330 core


uniform sampler2D materialTex0;
uniform sampler2D materialTex1;
uniform float flipping;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

in vec2 gUv0;
in vec3 gVertex;
in vec3 gNormal;
in vec3 gamb1;


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

	vec3 diffuse = diff(gVertex, -gNormal) * lightDiffuse;
	vec3 inColor = gamb1 + diffuse;
	
	diffuse = diff(gVertex, -gNormal) * lightDiffuse;
	vec3 outColor = gamb1 + diffuse;


	vec3 m1 = vec3(texture(materialTex0, gUv0));
	
	vec3 m2  = vec3(texture(materialTex1, gUv0));
	
	bool frontFace = (flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

	if(frontFace)
	{
		m1 *= vec3(inColor);
		fFragColor = vec4(m1,1);
	}
	else 
	{
		m2 *= vec3(outColor);
		fFragColor = vec4(m2,1);
	}
}
