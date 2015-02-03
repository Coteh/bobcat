#version 330

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
in vec3 vPosition; 
in vec3 vNormals;
in vec2 vTexture;
in vec3 vColor;
uniform mat3 normalMatrix;
uniform vec4 lightPos;  /// not used right now but you'll need it

smooth out vec3 vertNormal;
smooth out vec3 lightDir;
out vec2 texCoords; /// Pass the texture coordinates to the fragment shader

void main() {
	texCoords = vTexture; ///Pass them to the fragment shader

	vertNormal = vNormals.xyz; /// Rotate the normal to the correct orientation 
	mat4 modelViewMatrix = View * Model;
	vec4 eyePos = modelViewMatrix * vec4(vPosition, 0); /// Create the eye vector 
	lightDir = normalize(lightPos.xyz - eyePos.xyz); /// Create the light direction 

	gl_Position = Projection * modelViewMatrix * vec4(vPosition, 1.0);
}