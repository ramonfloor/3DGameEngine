#version 460 core

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{
    // Create checkerboard pattern based on X and Z coordinates
    int checkX = int(FragPos.x) / 50;
    int checkZ = int(FragPos.z) / 50;
    int checkSum = checkX + checkZ;
    
    vec3 baseColor = (checkSum % 2 == 0) ? vec3(0.2, 0.2, 0.2) : vec3(0.8, 0.8, 0.8);
    
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;

    // Normals and directions
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    // Ambient
    vec3 ambient = ambientStrength * lightColor * baseColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * baseColor;

    // Specular
    float shininess = 128.0;
    float specularStrength = 0.4;
    float spec = pow(max(dot(reflect(-lightDir, norm), normalize(ViewPos - FragPos)), 0.0f), shininess);
    vec3 specular = spec * lightColor * specularStrength;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}