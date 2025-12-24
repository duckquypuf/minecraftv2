#pragma once

#include <stdint.h>
#include <string>

struct Biome
{
    std::string name;

    uint8_t surfaceBlock;
    uint8_t subsurfaceBlock;
    uint8_t subsurfaceHeight;

    float frequency;
    float lacunarity;
    float gain;
    uint8_t octaves;

    int offset;

    int TERRAIN_MIN_HEIGHT;
    int TERRAIN_HEIGHT;
};