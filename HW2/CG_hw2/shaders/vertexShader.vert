#version 430

//// TODO: ////
//
// Hint:
// 1. Receive position, normal, texcoord from bind buffer
// 2. Receive Model matrix, View matrix, and Projection matrix from uniform
// 3. Pass texcoord and Normal to fragment shader (normal will not use in this homework)
// 4. Calculate view space by gl_Position (must be vec4)
//
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texcoord_in;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat4 bonus;

out vec3 normal;
out vec2 texcoord;

void main()
{
    gl_Position = Projection * ModelView * bonus *vec4(position, 1.0);
    normal = normal_in;
    texcoord = texcoord_in;
}
