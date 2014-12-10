#version 330 core

in vec3 vertexColor;

//lighting
in vec3 vertexWorld;
in vec3 normalWorld;
uniform vec3 lightPos;

out vec4 fColor;

void main()
{
	vec3 lightVectorWorld = normalize((lightPos).xyz - vertexWorld);
	//diffuse brightness
	float Kd = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuse = Kd * vec4(1.0,1.0,1.0,1.0);
	vec3 lcolor = clamp(diffuse.xyz, 0, 1);
	fColor = vec4(vertexColor, 1.0) * vec4(lcolor, 1.0);
}