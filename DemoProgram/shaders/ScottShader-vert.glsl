#version 330 core
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;
smooth out vec3 vertNormal;
smooth out vec3 lightDir;

//uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main() {
	vertNormal = vNormals.xyz; /// Rotate the normal to the correct orientation 
	mat4 modelViewMatrix = View * Model;
	vec4 eyePos = modelViewMatrix * vec4(vPosition, 0); /// Create the eye vector 
	lightDir = normalize(lightPos.xyz - eyePos.xyz); /// Create the light direction 

	gl_Position =  Projection * modelViewMatrix * vec4(vPosition, 1.0);
}