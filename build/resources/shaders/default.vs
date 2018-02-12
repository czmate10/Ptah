#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 Color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    Color = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = projection * view * model * vec4(pos, 1.0);
}