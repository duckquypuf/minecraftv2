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
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            for (int z = 0; z < WORLD_WIDTH; z++)
            {
                chunks[x][z] = new Chunk(this, ChunkCoord(x, z));
                chunks[x][z]->populateVoxelMap();
            }
        }

        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            for (int z = 0; z < WORLD_WIDTH; z++)
            {
                chunks[x][z]->mesh = new ChunkMesh();
                chunks[x][z]->mesh->buildMesh(chunks[x][z], this);
            }
        }
    }

    bool isVoxelTransparent(uint8_t blockID)
    {
        return blocks[blockID].type == AIR;
    }

    bool isVoxelTransparent(ChunkCoord coord, int localX, int localY, int localZ)
    {
        ChunkCoord real = coord;

        if (localX < 0)
        {
            localX = CHUNK_WIDTH - 1;
            real.x--;
        }
        else if (localX >= CHUNK_WIDTH)
        {
            localX = 0;
            real.x++;
        }

        if (localZ < 0)
        {
            localZ = CHUNK_WIDTH - 1;
            real.z--;
        }
        else if (localZ >= CHUNK_WIDTH)
        {
            localZ = 0;
            real.z++;
        }

        if (localY < 0 || localY >= CHUNK_HEIGHT)
        {
            return true;
        }

        if (real.x < 0 || real.x >= WORLD_WIDTH ||
            real.z < 0 || real.z >= WORLD_WIDTH)
        {
            return true;
        }

        return isVoxelTransparent(chunks[real.x][real.z]->voxelMap[localX][localY][localZ]);
    }

    uint8_t getVoxel(ChunkCoord coord, int x, int y, int z)
    {
        uint8_t voxel = 0;

        if (y == CHUNK_HEIGHT - 1)
            voxel = 1; // Grass
        else if (y >= 0)
            voxel = 2; // Stone

        return voxel;
    }
};