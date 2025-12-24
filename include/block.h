#pragma once

#include <array>

enum BlockType
{
    AIR = -1,
    SOLID = 0,
    TRANSPARENT = 1,
};

class Block
{
public:
    const char* name;
    BlockType type;
    std::array<uint8_t, 6> textureIDs;

    Block(const char *name, BlockType type, std::array<uint8_t, 6> textureIDs)
        : name(name), type(type), textureIDs(textureIDs)
    {
    }
};