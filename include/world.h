#pragma once

#include "voxelData.h"
#include "chunk.h"

class World
{
public:
    Chunk* chunks[WORLD_WIDTH][WORLD_WIDTH];

    World()
    {
        generateChunks();
    }

    void generateChunks()
    {
        for(int x = 0; x < WORLD_WIDTH; x++)
        {
            for(int z = 0; z < WORLD_WIDTH; z++)
            {
                chunks[x][z] = new Chunk(this, ChunkCoord(x, z));
            }
        }
    }

    bool isVoxelTransparent(uint8_t blockID)
    {
        return blocks[blockID].type == AIR;
    }
};