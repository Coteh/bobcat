#version 330 core
uniform mat4 Model, Camera, Perspective_Projection;
attribute vec3 vPosition;
attribute vec3 vNormals;
attribute vec2 vTexture;
attribute vec3 vColor;

out vec3 VertexColor;

void main()
{
	gl_Position = Perspective_Projection * Camera * Model * vec4(vPosition,1.0);
	VertexColor = vNormals;
}