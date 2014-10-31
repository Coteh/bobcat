#version 330 core
uniform mat4 Model, Camera, Perspective_Projection;
layout(location = 0) in vec4 vPosition;

out vec3 varyingNormal;
out vec3 VertexColor;

void main()
{
	gl_Position = Perspective_Projection * Camera * Model * vPosition;
	varyingNormal = normalize(gl_Position).xyz;
	VertexColor.xyz = vPosition.xyz;
}
