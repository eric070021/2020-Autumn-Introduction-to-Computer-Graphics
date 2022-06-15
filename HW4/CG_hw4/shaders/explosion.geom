#version 430 core
layout(triangles) in;
layout(points, max_vertices = 1) out;

in VS_OUT {
    vec3 normal;
    vec2 Texcoord;
} gs_in[];

uniform mat4 P;
uniform float time;
uniform float explode_time;

out vec4 color;

void main()
{
    color=vec4(1.0,1.0,1.0,1.0);
    vec3 pointnorm = (gs_in[0].normal + gs_in[1].normal + gs_in[2].normal)/3;
    gl_Position = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3) + vec4(pointnorm, 0.0f) * (1.0f*explode_time + (1/2)*0.1*explode_time*explode_time);
    EmitVertex();
    EndPrimitive();
}
