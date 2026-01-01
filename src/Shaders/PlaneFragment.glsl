#version 460 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;

void main()
{
    int checkX = int(floor(FragPos.x * 2.0f));
    int checkZ = int(floor(FragPos.z * 2.0f));
    vec3 baseColor = mod(checkX + checkZ, 2) == 0 ? vec3(0.8f, 0.8f, 0.8f) : vec3(0.2f, 0.2f, 0.2f);
    
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = 0.2f * light_color;

    vec3 norm = normalize(Normal);
    vec3 direction = normalize(LightPos - FragPos);
    float k_d = max(dot(norm, direction), 0.0f);
    vec3 diffuse = k_d * light_color;

    vec3 light = (ambient + diffuse) * baseColor;

    FragColor = vec4(light, 1.0f);
}