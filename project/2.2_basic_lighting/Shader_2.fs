#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(0.0f, dot(lightDir, normal));
	vec3 diffuse = diff * lightColor;
	vec3 result = (diffuse + ambient) * objectColor;
	FragColor = vec4(result, 1.0f);
};