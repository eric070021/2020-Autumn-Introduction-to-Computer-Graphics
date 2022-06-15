#version 430

uniform sampler2D texture;
uniform vec3 WorldLightPos;
uniform vec3 Kd;

in vec2 Texcoord;
in vec3 FragNormal;
in vec3 FragPos;

float intensity;

out vec4 color;
void main()
{
    vec4 object_color = texture2D(texture, Texcoord);

    vec3 lightDir = normalize(WorldLightPos - FragPos);
    vec3 normal = normalize(FragNormal);
    float level = dot(lightDir, normal);

    if (level > 0.95)
        intensity = 1;
    else if (level > 0.75)
        intensity = 0.8;
    else if (level > 0.5)
        intensity = 0.6;
    else if (level > 0.25)
        intensity = 0.4;
    else
        intensity = 0.2;

    vec3 result = Kd * intensity * vec3(object_color);
    color = vec4(result, 1.0f);
} 