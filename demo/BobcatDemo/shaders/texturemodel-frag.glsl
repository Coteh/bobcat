#version 330 core

//uniform color
uniform vec4 uniColor;

//in tex coords from vertex shader
in vec2 texCoords;
//uniform texture sampler
uniform sampler2D tex;

//in lighting
in vec3 vertexWorld;
in vec3 normalWorld;
uniform vec3 LightPos;

//out color
out vec4 fColor;

void main()
{
	vec3 lightVectorWorld = normalize((LightPos).xyz - vertexWorld);

	//diffuse brightness
	float Kd = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuse = Kd * vec4(1.0,1.0,1.0,1.0);
	vec3 diffuseClamped = clamp(diffuse.xyz, 0, 1);

	fColor = texture(tex, texCoords) * uniColor/* * vec4(diffuseClamped, 1)*/;
}
