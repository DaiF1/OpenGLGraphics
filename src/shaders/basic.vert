#version 460 core

layout(location = 0) in vec4 aColor;
layout(location = 1) in vec3 aPosition;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
}
