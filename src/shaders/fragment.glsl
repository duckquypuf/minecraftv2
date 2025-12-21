#version 410 core

in vec2 pos;

out vec4 Colour;

void main()
{
    Colour = vec4(gl_FragCoord.xy, 0.0, 1.0);
}