#include "chunk.h"
#include "world.h"

void Chunk::populateVoxelMap()
{
    for (int y = 0; y < CHUNK_HEIGHT; y++)
    {
        for (int x = 0; x < CHUNK_WIDTH; x++)
        {
            for (int z = 0; z < CHUNK_WIDTH; z++)
            {
                voxelMap[x][y][z] = world->getVoxel(coord, x, y, z);
            }
        }
    }
}