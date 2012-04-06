#version 330 core

#define POSITION 0
precision highp float;
precision highp int;

uniform mat4 MVP;
uniform float Time_t;

layout(location = POSITION) in vec2 Position;

void main()
{
        gl_Position = MVP * vec4(Position,0.25,1.0) + vec4(0.0,sin(360*Time_t),0.0,0.0)+vec4(0.0,cos(360*Time_t),0.0,0.0);;
}
