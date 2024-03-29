#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 inFragPos;
out vec3 inNormal;
out vec2 inTexCoord;

uniform mat4 _model;

void main()
{
    gl_Position = _model * vec4(aPos, 1.0);
    inFragPos = gl_Position.xyz;
    inNormal = aNormal;
    inTexCoord = aTexCoord;
}