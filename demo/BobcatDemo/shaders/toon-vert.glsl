#version 330
in vec3 vPosition;
in vec3 vNormals;
in vec2 vTexture;
in vec3 vColor;
smooth out vec3 normal;
smooth out vec3 lightDir;
smooth out vec4 eyePos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat3 NormalMatrix;
uniform vec4 LightPos;

void main() {
  //Combine View and Model into ModelView
  mat4 modelViewMatrix = View * Model;

  /// Rotate the normal to the correct orientation
	normal = NormalMatrix * vNormals;

  /// Create the eye vector
	eyePos = modelViewMatrix * vec4(vPosition, 0.7);

  /// Create the light direction
	lightDir = normalize(LightPos.xyz - eyePos.xyz);

  //Determine GL position
	gl_Position =  Projection * modelViewMatrix * vec4(vPosition, 1.0);
}
