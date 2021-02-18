#shader vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCooord;
out vec2 inTexCoord;

uniform mat4 _projection;

void main()
{
    gl_Position = _projection * vec4(aPos, 1.0);
    inTexCoord = aTexCooord;
}

#shader fragment

#version 330 core
in vec2 inTexCoord;
out vec4 fragOut;

uniform sampler2D _textTexture;
uniform vec4 _textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(_textTexture, inTexCoord).r);
    fragOut = _textColor * sampled;
    // fragOut = vec4(1.0, 1.0, 1.0, 0.5);
}