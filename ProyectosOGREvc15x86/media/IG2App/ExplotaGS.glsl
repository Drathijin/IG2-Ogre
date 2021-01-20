#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 modelViewProjMat;
uniform float time;
const float VD = 50;
in vec2 vUv0[];
in vec3 vNormal[];
in vec3 vVertex[];
in vec3 amb1[];

out vec2 gUv0;
out vec3 gNormal;
out vec3 gVertex;
out vec3 gamb1;
vec3 normalVec(vec3 vertex[3])
{
	vec3 a = vertex[0];
	vec3 b = vertex[1];
	vec3 c = vertex[2];
	return normalize(cross(b-a,c-a));
}


void main()
{
	vec3 vertices[3] = vec3[](gl_in[0].gl_Position.xyz,
							  gl_in[1].gl_Position.xyz,
							  gl_in[2].gl_Position.xyz);
	vec3 dir = normalVec(vertices) * time;
	
	for(int i=0; i<3;i++)
	{
		vec3 posDes = vertices[i] + dir * VD;
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);
		gUv0 = vUv0[i];
		gNormal = vNormal[i];
		gamb1 = amb1[i];
		gVertex = vVertex[i];
		EmitVertex();
	}

	EndPrimitive();
}