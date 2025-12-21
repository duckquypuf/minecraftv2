#version 410 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D atlasTexture;

const int atlasWidth = 16;

void main()
{
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diff = max(dot(Normal, lightDir), 0.3);
    FragColor = vec4(vec3(0.5, 0.8, 0.3) * diff, 1.0);
}