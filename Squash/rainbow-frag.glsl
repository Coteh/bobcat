#version 330 core

in vec3 VertexColor;

out vec4 fColor;

void main()
{
	fColor = vec4(VertexColor, 1.0);
}