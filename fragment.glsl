#version 330 core

#define FRAG_COLOR 0

precision highp float;
precision highp int;

uniform vec4 Diffuse;
uniform float Time_t;

layout(location = FRAG_COLOR,index=0) out vec4 Color;

void main()
{
    float lerpColor = gl_FragCoord.y / 500.0f;
    Color = mix(vec4(1.0,1.0,1.0,1.0),
                vec4(0.5,0.2,0.2,0.2),lerpColor);
}
