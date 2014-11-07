#version 330 core
uniform mat4 Model, Camera, Perspective_Projection;
layout(location = 0) in vec4 vPosition;

void main()
{
	gl_Position = Perspective_Projection * Camera * Model * vPosition;
}
