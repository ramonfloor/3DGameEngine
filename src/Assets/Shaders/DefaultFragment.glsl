#version 460 core

in vec3 Normal;
in vec3 Color;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{   
    vec3 baseColor = Color;
    
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.3f;

    // Normals and directions
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    // Ambient
    vec3 ambient = ambientStrength * lightColor * baseColor;

    // Diffuse
    float diffuseStrength = 1.0f;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor * baseColor;

    // Specular
    float shininess = 32.0;
    float specularStrength = 0.5;
    float spec = pow(max(dot(reflect(-lightDir, norm), normalize(ViewPos - FragPos)), 0.0f), shininess);
    vec3 specular = spec * lightColor * specularStrength;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}