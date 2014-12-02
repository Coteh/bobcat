#version 330 core

in vec4 vertexColor;
in vec2 texCoords;

out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor = texture(tex, texCoords);
}