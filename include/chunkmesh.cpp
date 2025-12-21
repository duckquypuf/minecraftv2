#include "chunkmesh.h"
#include "chunk.h"
#include "world.h"

void ChunkMesh::addFace(Chunk *chunk, int faceIndex, int x, int y, int z)
{
    int offset = faceIndex * 6 * 8;

    for (int i = 0; i < 6 * 8; i += 8)
    {
        vertices.push_back(cubeVertices[offset + i + 0] + x);
        vertices.push_back(cubeVertices[offset + i + 1] + y);
        vertices.push_back(cubeVertices[offset + i + 2] + z);

        vertices.push_back(cubeVertices[offset + i + 3]);
        vertices.push_back(cubeVertices[offset + i + 4]);
        vertices.push_back(cubeVertices[offset + i + 5]);

        vertices.push_back(cubeVertices[offset + i + 6]);
        vertices.push_back(cubeVertices[offset + i + 7]);

        vertices.push_back(blocks[chunk->voxelMap[x][y][z]].textureIDs[faceIndex]);
    }
}

void ChunkMesh::addBlockFaces(Chunk* chunk, World* world, int x, int y, int z, uint8_t blockID)
{
    for (int face = 0; face < 6; face++)
    {
        int nx = x + faceChecks[face * 3 + 0];
        int ny = y + faceChecks[face * 3 + 1];
        int nz = z + faceChecks[face * 3 + 2];

        bool solidNeighbor =
            nx >= 0 && nx < CHUNK_WIDTH &&
            ny >= 0 && ny < CHUNK_HEIGHT &&
            nz >= 0 && nz < CHUNK_WIDTH &&
            !world->isVoxelTransparent(chunk->voxelMap[nx][ny][nz]);

        if (solidNeighbor)
            continue;

        addFace(chunk, face, x, y, z);
    }
}

void ChunkMesh::buildMesh(Chunk *chunk, World *world)
{
    vertices.clear();

    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_WIDTH; z++)
            {
                uint8_t blockID = chunk->voxelMap[x][y][z];
                if (blockID == 0)
                    continue;

                addBlockFaces(chunk, world, x, y, z, blockID);
            }
        }
    }

    upload();
}