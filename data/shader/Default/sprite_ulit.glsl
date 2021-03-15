////////////////////////////
/// Copyright: Kpurek
/// Repo: https://github.com/Kpure1000/HazelEngine
////////////////////////////

////////////////////////////
/// vertex shader
////////////////////////////

#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCooord;
layout (location = 3) in float aTexIndex;

out vec3 inFragPos;
out vec4 inColor;
out vec2 inTexCoord;
flat out int inTexIndex;

uniform mat4 _view_prj; 

void main()
{
    gl_Position = _view_prj * vec4(aPos, 1.0);
    
    inFragPos = gl_Position.xyz;
    inColor = aColor;
    inTexCoord = aTexCooord;
    inTexIndex=int(aTexIndex);
}

////////////////////////////
/// fragment shader
////////////////////////////

#shader fragment
#version 330 core

in vec3 inFragPos;
in vec4 inColor;
in vec2 inTexCoord;
flat in int inTexIndex;

out vec4 fragOut;

uniform sampler2D _textures[32];

void main()
{
    fragOut = inColor * texture(_textures[inTexIndex], inTexCoord);
}