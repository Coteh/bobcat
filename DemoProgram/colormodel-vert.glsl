#version 330 core
uniform mat4 MVP;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

out vec3 vertexColor;

void main()
{
	gl_Position = MVP * vec4(vPosition, 1.0);
	vertexColor = vColor;
}
