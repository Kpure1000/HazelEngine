#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCooord;

out vec3 inFragPos;
out vec3 inNormal;
out vec2 inTexCoord;

uniform mat4 _model;

void main()
{
    inFragPos = vec3(_model * vec4(aPos, 1.0));
    inNormal = mat3(transpose(inverse(_model))) * aNormal;
    inTexCoord = aTexCooord;
    gl_Position = _model * vec4(aPos, 1.0);
}