#version 330 core
uniform mat4 Model, Camera, Perspective_Projection;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

void main()
{
	gl_Position = Perspective_Projection * Camera * Model * vec4(vPosition, 1.0);
}
