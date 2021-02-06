#version 430 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 fragOut;

uniform sampler2D _diffuse;

void main()
{
    fragOut = normalize(texture(_diffuse, inTexCoord));
}