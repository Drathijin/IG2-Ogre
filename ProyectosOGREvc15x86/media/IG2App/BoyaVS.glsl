#version 330 core


uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 normalMat;


uniform vec3 lightAmbient;

uniform vec4 InColor;
uniform vec4 OutColor; 

in vec4 vertex;
in vec3 normal;
in vec2 uv0;


out vec2 vUv0;
out vec3 vVertex;
out vec3 vNormal;
out vec3 amb1;
out vec3 amb2;


void main()
{
	amb1 = lightAmbient * vec3(InColor);
	amb2 = lightAmbient * vec3(OutColor);

	vec3 viewVertex = vec3(modelViewMat * vertex);
	vec3 viewNormal = normalize(vec3(normalMat * vec4(normal, 0)));

	vUv0 = uv0;
	vVertex = viewVertex;
	vNormal = viewNormal;
	gl_Position = modelViewProjMat * vertex;
}
