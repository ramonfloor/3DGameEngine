#version 460 core

in vec3 VertexColor;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 lightColor = vec3(1.0);
    vec3 objectColor = VertexColor;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
        
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}