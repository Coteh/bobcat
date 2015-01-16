#version 330 core
uniform mat4 MVP;
attribute vec3 vPosition;
attribute vec3 vNormals;
attribute vec2 vTexture;
attribute vec3 vColor;

out vec3 vertexColor;
//lighting
out vec3 vertexWorld;
out vec3 normalWorld;

void main()
{
	//Calculate GL position
	gl_Position = MVP * vec4(vPosition,1.0);

	//Transform vertex position into eye coordinates
	vertexWorld = gl_Position.xyz;

	//Use normals
	mat3 norm = mat3(MVP);
	normalWorld = normalize(norm * vNormals);

	//Determine what the color to send to the shader is
	vertexColor = vNormals;
}