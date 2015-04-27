#version 330

in  vec3 vertNormal;
in  vec3 lightDir;
in  vec2 texCoords;
uniform sampler2D myTexture0;
uniform vec4 uniColor;

out vec4 outColor;

void main() {
	float ambStrength = 0.4;
	vec3 ambient = ambStrength * vec3(1.0,1.0,1.0);

	/// The reflect() method this most GPU expensive step in this proceedure
	/// The Blinn-Phong method is faster. Know why.
	// Because it just makes an approximation of the reflect value?
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float diff = max(dot(vertNormal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0,1.0,1.0);
	float spec = max(0.0, dot(vertNormal, reflection));
	if(diff != 0.0){
		spec = pow(spec,16.0);
	}
	vec3 specular = spec * vec3(0.5, 0.5, 0.5);

	vec3 result = ambient + diffuse + specular;

	outColor = texture(myTexture0,texCoords) * uniColor * vec4(result, 1.0);
}
