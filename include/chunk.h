#pragma once

#include <cstdint>

#include "voxelData.h"

struct ChunkCoord
{
    int x, z;

    ChunkCoord()
    {
        x = 0;
        z = 0;
    }

    ChunkCoord(int _x, int _z)
    {
        x = _x;
        z = _z;
    }

    bool operator==(const ChunkCoord &other) const
    {
        return other.x == x && other.z == z;
    }
};

class World;
class ChunkMesh;

class Chunk
{
public:
    ChunkCoord coord;
    ChunkMesh* mesh;

    uint8_t voxelMap[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

    Chunk(World* world, ChunkCoord coord)
    {
        this->world = world;
        this->coord.x = coord.x;
        this->coord.z = coord.z;
    }

    void populateVoxelMap()
    {
        for(int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int x = 0; x < CHUNK_WIDTH; x++)
            {
                for (int z = 0; z < CHUNK_WIDTH; z++)
                {
                    voxelMap[x][y][z] = 1;
                }
            }
        }
    }

private:
    World* world;
};