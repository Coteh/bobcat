#version 330 core
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

//out tex coords
out vec2 texCoords;

//out lighting
out vec3 vertexWorld;
out vec3 normalWorld;
out vec4 outPos;

void main()
{
	//Calculare Out Position
	outPos = Model * vec4(vPosition, 1.0);

	//Calculate GL position
	gl_Position = Projection * View * outPos;

	//Transform vertex position into eye coordinates
	vertexWorld = gl_Position.xyz;

	//Use normals
	mat3 norm = mat3(Model);
	normalWorld = normalize(norm * vNormals);

	//Send texture coordinates to the fragment shader
	texCoords = vTexture;
}
