#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 normal;
    vec2 Texcoord;
} gs_in[];

uniform mat4 P;
uniform float time;

out vec2 TexCoords;

void heartbeat(int index){
    if(index==0){
        gl_Position = gl_in[0].gl_Position + vec4(gs_in[0].normal, 0.0f)*((sin(time) + 1.0f) / 2.0f) * (time-23)/2;
        TexCoords = gs_in[0].Texcoord;
        EmitVertex();
    }
    else if(index==1){
        gl_Position = gl_in[1].gl_Position + vec4(gs_in[1].normal, 0.0f)*((sin(time) + 1.0f) / 2.0f) * (time-23)/2;
        TexCoords = gs_in[1].Texcoord;
        EmitVertex();
    }
    else{
        gl_Position = gl_in[2].gl_Position + vec4(gs_in[2].normal, 0.0f)*((sin(time) + 1.0f) / 2.0f) * (time-23)/2;
        TexCoords = gs_in[2].Texcoord;
        EmitVertex();
        EndPrimitive();
    }
}

void main()
{
    for(int i=0;i<gl_in.length();i++){
        heartbeat(i);
    }
}
