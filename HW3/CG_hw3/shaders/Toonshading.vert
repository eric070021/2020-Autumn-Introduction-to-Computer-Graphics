#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texcoord;

uniform mat4 M, V, P;
out vec2 Texcoord;
out vec3 FragNormal;
out vec3 FragPos;

void main() {
  gl_Position = P * V * M * vec4(in_position, 1.0);
  FragPos = vec3(M * vec4(in_position, 1.0)); 
  Texcoord = texcoord;
  mat3 normalMatrix = mat3(transpose(inverse(M)));
  FragNormal = normalMatrix * normal_in;

}
