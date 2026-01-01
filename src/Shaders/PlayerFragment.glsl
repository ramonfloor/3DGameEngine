#version 460 core

in vec3 VertexColor;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;

void main()
{
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = 0.2f * light_color;

    vec3 norm = normalize(Normal);
    vec3 direction = normalize(LightPos - FragPos);
    float k_d = max(dot(norm, direction), 0.0f);
    vec3 diffuse = k_d * light_color;

    vec3 light = (ambient + diffuse) * VertexColor;

    FragColor = vec4(light, 1.0f);
}