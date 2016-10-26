#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 position;
uniform vec2 scale;
uniform vec2 translate;

void main(){

    gl_Position.xy =  (position * scale) + translate;
    gl_Position.w = 1;
}

