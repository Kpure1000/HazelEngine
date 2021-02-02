#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 fragOut;

void main()
{
    fragOut = vec4(normalize((inNormal + 1.0) / 2.0), 1.0);
}