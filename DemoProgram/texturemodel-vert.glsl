#version 330 core
uniform mat4 MVP;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

//out tex coords
out vec2 texCoords;

//out lighting
out vec3 vertexWorld;
out vec3 normalWorld;

void main()
{
	//Calculate GL position
	gl_Position = MVP * vec4(vPosition, 1.0);

	//Transform vertex position into eye coordinates
	vertexWorld = gl_Position.xyz;

	//Use normals
	mat3 norm = mat3(MVP);
	normalWorld = normalize(norm * vNormals);

	//Send texture coordinates to the fragment shader
	texCoords = vTexture;
}
