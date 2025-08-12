#version 410 core

in vec3 vertexColor;

out vec4 finalColor;

void main()
{
    finalColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
}