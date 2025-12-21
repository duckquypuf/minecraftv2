#pragma once

#include "voxelData.h"
#include "chunk.h"
#include "chunkmesh.h"

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
            for (int z = 0; z < WORLD_WIDTH; z++)
            {
                chunks[x][z] = new Chunk(this, ChunkCoord(x, z));
                chunks[x][z]->populateVoxelMap();                  
                chunks[x][z]->mesh = new ChunkMesh();              
                chunks[x][z]->mesh->buildMesh(chunks[x][z], this); 
            }
        }
    }

    bool isVoxelTransparent(uint8_t blockID)
    {
        return blocks[blockID].type == AIR;
    }
};