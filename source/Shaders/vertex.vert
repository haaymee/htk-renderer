#version 410 core

uniform vec3 u_posOffset;
uniform float u_time;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
    float posOffset = (sin(u_time * 5.f) / 50.f);
    
    vertexColor = color;
    gl_Position = vec4(u_posOffset, 0.f) + vec4(position.x, position.y + posOffset, position.z, 1.0f);
}