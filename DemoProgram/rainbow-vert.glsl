#version 330 core
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
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
	//Calculate ModelViewProjection
	mat4 mvp = Projection * View * Model;

	//Calculate GL position
	gl_Position = mvp * vec4(vPosition, 1.0);

	//Transform vertex position into eye coordinates
	vertexWorld = gl_Position.xyz;

	//Use normals
	mat3 norm = mat3(Model);
	normalWorld = normalize(norm * vNormals);

	//Determine what the color to send to the shader is
	vertexColor = vNormals;
}