#version 330 core

varying vec3 varyingNormal;
uniform vec3 lightDirection;
varying vec3 VertexColor;

out vec4 fColor;

void main()
{
	float lighting = (varyingNormal.x * lightDirection.x) + (varyingNormal.y * lightDirection.y) + (varyingNormal.z * lightDirection.z);
	fColor = vec4(VertexColor, 1.0);
}