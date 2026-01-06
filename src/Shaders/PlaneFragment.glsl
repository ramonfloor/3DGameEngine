#version 460 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ViewPos;

void main()
{
    // Checkerboard base color
    int checkX = int(floor(FragPos.x * 2.0));
    int checkZ = int(floor(FragPos.z * 2.0));
    vec3 baseColor = (mod(float(checkX + checkZ), 2.0) == 0.0) ? vec3(0.8, 0.8, 0.8) : vec3(0.2, 0.2, 0.2);


    // Normals and directions
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    // Ambient
    vec3 ambient = ambientStrength * lightColor * baseColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * baseColor;

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
}