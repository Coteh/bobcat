#version 330 core
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

out vec3 vertexColor;

void main()
{
	//Calculate ModelViewProjection
	mat4 mvp = Projection * View * Model;

	vec3 pos = vPosition;

	pos.xyz = vNormals.xyz * vTexture.x * Time;

	vertexColor = vColor;

	//Calculate GL position
	gl_Position = mvp * vec4(pos, 1.0);
}
