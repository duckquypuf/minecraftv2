#version 410 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in float TextureID;

uniform sampler2D atlasTexture;

out vec4 FragColor;

void main()
{
    // Atlas configuration
    const float ATLAS_SIZE = 16.0;  // 16x16 grid
    const float TILE_SIZE = 1.0 / ATLAS_SIZE;
    
    // Calculate which tile to use
    float tileX = mod(TextureID, ATLAS_SIZE);
    float tileY = floor(TextureID / ATLAS_SIZE);
    
    // Calculate UV offset for this tile
    vec2 tileOffset = vec2(tileX, tileY) * TILE_SIZE;
    
    // Scale the texture coordinates to fit within one tile
    vec2 scaledUV = TexCoord * TILE_SIZE;
    
    // Final UV coordinates
    vec2 finalUV = tileOffset + scaledUV;
    
    // Sample the texture
    vec4 texColor = texture(atlasTexture, finalUV);
    
    // Simple directional lighting
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diff = max(dot(normalize(Normal), lightDir), 0.5);
    
    // Apply lighting to texture
    vec3 result = texColor.rgb * diff;
    
    FragColor = vec4(result, texColor.a);
}