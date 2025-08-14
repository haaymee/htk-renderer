#version 410 core

uniform float u_time;

uniform mat4 u_modelMatrix;
uniform mat4 u_projectionMatrix;


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
    vertexColor = color;
    
    float posOffset = (sin(u_time * 5.f) / 50.f);
    
    vec4 finalPosition = u_projectionMatrix * u_modelMatrix * vec4(position.x, position.y + posOffset, position.z, 1.0f); 
    gl_Position = finalPosition;
}