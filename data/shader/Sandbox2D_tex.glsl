#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCooord;

out vec3 inFragPos;
out vec3 inNormal;
out vec2 inTexCoord;

uniform mat4 _model;
uniform mat4 _view_prj; 

void main()
{
    gl_Position = _view_prj * _model * vec4(aPos, 1.0);
    inFragPos = gl_Position.xyz;
    inNormal = mat3(transpose(inverse(_model))) * aNormal;
    inTexCoord = aTexCooord;
}


#shader fragment
#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 fragOut;

uniform sampler2D _tx;

void main()
{
    fragOut = texture(_tx, inTexCoord);
}