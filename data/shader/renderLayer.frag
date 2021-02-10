#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 fragOut;

uniform sampler2D _diffuse;

void main()
{
    fragOut = texture(_diffuse, inTexCoord);
    //  Test TexCoord: 
    fragOut += vec4(inTexCoord.x, inTexCoord.y, 0.0, 1.0);
    fragOut /= 2;
}