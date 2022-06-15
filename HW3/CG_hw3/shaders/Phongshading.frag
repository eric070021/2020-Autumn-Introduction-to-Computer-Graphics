#version 430

uniform sampler2D texture;
uniform vec3 WorldLightPos, WorldCamPos;
uniform vec3 Ka, Kd, Ks, La, Ld, Ls;
uniform float gloss;

in vec2 Texcoord;
in vec3 FragNormal;
in vec3 FragPos;

out vec4 color;
void main()
{
    vec4 object_color = texture2D(texture, Texcoord);

    vec3 ambient = Ka * La * vec3(object_color);

    vec3 lightDir = normalize(WorldLightPos - FragPos);
    vec3 normal = normalize(FragNormal);
    float diffFactor = max(dot(lightDir, normal), 0.0);
    vec3 diffuse =  Kd * Ld * diffFactor * vec3(object_color);

    vec3    reflectDir = normalize(reflect(-lightDir, normal));
    vec3    viewDir = normalize(WorldCamPos - FragPos);
    float   specFactor = pow(max(dot(reflectDir, viewDir), 0.0), gloss); 
    vec3    specular = Ks * Ls * specFactor * vec3(object_color);

    vec3 result = ambient + diffuse + specular;

    color = vec4(result, 1.0f);
} 