#version 430

uniform vec3 WorldCamPos;

in vec3 FragNormal;
in vec3 FragPos;
float show;

vec4 red = vec4(0.0, 0.0, 1.0, 1.0);
out vec4 color;

void main()
{
    vec3 normal = normalize(FragNormal);

    vec3 CameraDir = normalize(WorldCamPos - FragPos);
    float edge = dot(CameraDir, normal);

    if (edge < 0.2)
        show = 1.0;
    else    
        show = 0.0;

    color = show * red;
} 