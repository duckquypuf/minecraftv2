#pragma once

#include <iostream>

#include "voxelData.h"
#include "chunk.h"
#include "chunkmesh.h"

class World
{
public:
    Chunk* chunks[WORLD_WIDTH][WORLD_WIDTH];

    World()
    {
        // --- Initialise Biome Noise ---
        biomeNoise.SetSeed(1038);
        biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        biomeNoise.SetFrequency(0.01f);
        biomeNoise.SetFractalOctaves(2);

        // --- Initialise Noise ---
        noise.SetSeed(1738);
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFrequency(0.02f);
        noise.SetFractalOctaves(3);

        terrainNoise.SetSeed(1738);
        terrainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    }

    void generateChunks()
    {
        for (int x = HALF_WORLD_WIDTH - RENDER_DISTANCE; x < HALF_WORLD_WIDTH + RENDER_DISTANCE; x++)
        {
            for (int z = HALF_WORLD_WIDTH - RENDER_DISTANCE; z < HALF_WORLD_WIDTH + RENDER_DISTANCE; z++)
            {
                chunks[x][z] = new Chunk(this, ChunkCoord(x, z));
                chunks[x][z]->populateVoxelMap();
            }
        }

        for (int x = HALF_WORLD_WIDTH - RENDER_DISTANCE; x < HALF_WORLD_WIDTH + RENDER_DISTANCE; x++)
        {
            for (int z = HALF_WORLD_WIDTH - RENDER_DISTANCE; z < HALF_WORLD_WIDTH + RENDER_DISTANCE; z++)
            {
                chunks[x][z]->mesh = new ChunkMesh();

                chunks[x][z]->mesh->buildMesh(chunks[x][z], this);
            }
        }
    }

    void updateRenderDistance(ChunkCoord lastPlayerCoord)
    {
        for (int x = lastPlayerCoord.x - RENDER_DISTANCE; x < lastPlayerCoord.x + RENDER_DISTANCE; x++)
        {
            for (int z = lastPlayerCoord.z - RENDER_DISTANCE; z < lastPlayerCoord.z + RENDER_DISTANCE; z++)
            {
                if(x < 0 || x >= WORLD_WIDTH || z < 0 || z >= WORLD_WIDTH) 
                    continue;

                Chunk* chunk = chunks[x][z];

                if(chunk == nullptr || !chunk->isVoxelMapPopulated)
                {
                    chunks[x][z] = new Chunk(this, ChunkCoord(x, z));
                    chunks[x][z]->populateVoxelMap();
                }
            }
        }

        for (int x = lastPlayerCoord.x - RENDER_DISTANCE; x < lastPlayerCoord.x + RENDER_DISTANCE; x++)
        {
            for (int z = lastPlayerCoord.z - RENDER_DISTANCE; z < lastPlayerCoord.z + RENDER_DISTANCE; z++)
            {
                if (x < 0 || x >= WORLD_WIDTH || z < 0 || z >= WORLD_WIDTH)
                    continue;

                Chunk *chunk = chunks[x][z];

                if (!chunk->isMeshGenerated)
                {
                    chunks[x][z]->mesh = new ChunkMesh();
                    chunks[x][z]->mesh->buildMesh(chunks[x][z], this);
                }
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

        Chunk* chunk = chunks[real.x][real.z];

        if (chunk == nullptr || !chunk->isVoxelMapPopulated)
            return true;

        return isVoxelTransparent(chunk->voxelMap[localX][localY][localZ]);
    }

    bool isVoxelSolid(uint8_t blockID)
    {
        return blocks[blockID].type == SOLID;
    }

    bool isVoxelSolid(ChunkCoord coord, int localX, int localY, int localZ)
    {
        int chunkX = coord.x;
        int chunkZ = coord.z;

        if (localX < 0)
        {
            chunkX--;
            localX = CHUNK_WIDTH - 1;
        }
        else if (localX > CHUNK_WIDTH - 1)
        {
            chunkX++;
            localX = 0;
        }

        if (localZ < 0)
        {
            chunkZ--;
            localZ = CHUNK_WIDTH - 1;
        }
        else if (localZ > CHUNK_WIDTH - 1)
        {
            chunkZ++;
            localZ = 0;
        }

        if (localY < 0 || localY > CHUNK_HEIGHT - 1)
            return false;
        
        if(chunkX < 0 || chunkX >= WORLD_WIDTH || chunkZ < 0 || chunkZ >= WORLD_WIDTH)
            return false;
        
        Chunk* chunk = chunks[chunkX][chunkZ];

        if(chunk == nullptr || !chunk->isVoxelMapPopulated)
            return false;

        return isVoxelSolid(chunks[chunkX][chunkZ]->voxelMap[localX][localY][localZ]);
    }

    bool isVoxelSolid(int worldX, int worldY, int worldZ)
    {
        ChunkCoord coord = ChunkCoord();

        coord.x = floor(worldX / CHUNK_WIDTH);
        coord.z = floor(worldZ / CHUNK_WIDTH);

        int localX = worldX % CHUNK_WIDTH;
        int localZ = worldZ % CHUNK_WIDTH;

        return isVoxelSolid(coord, localX, worldY, localZ);
    }

    // Standard biome generation approach (like Minecraft)
    uint8_t getVoxel(ChunkCoord coord, int x, int y, int z)
    {
        if(y == 0) return 2; // Stone (change to bedrock)

        uint8_t voxel = 0;

        float worldX = (float)coord.x * CHUNK_WIDTH + x;
        float worldZ = (float)coord.z * CHUNK_WIDTH + z;

        float climateScale = 0.05f;

        float temperature = biomeNoise.GetNoise(worldX * climateScale, worldZ * climateScale);

        float humidity = biomeNoise.GetNoise(worldX * climateScale + 10000, worldZ * climateScale + 10000);

        int selectedBiome = 0;

        if (temperature < 0.5f && humidity < 0.5f)
        {
            selectedBiome = 0; // Cold & Dry = Tundra/Plains
        }
        else if (temperature < 0.5f && humidity >= 0.5f)
        {
            selectedBiome = 1; // Cold & Wet = Taiga
        }
        else if (temperature >= 0.5f && humidity < 0.5f)
        {
            selectedBiome = 1; // Hot & Dry = Desert
        }
        else
        {
            selectedBiome = 0; // Hot & Wet = Jungle
        }

        const Biome &biome = biomes[selectedBiome];

        terrainNoise.SetFrequency(biome.frequency);
        terrainNoise.SetFractalOctaves(biome.octaves);
        terrainNoise.SetFractalLacunarity(biome.lacunarity);
        terrainNoise.SetFractalGain(biome.gain);

        float noiseValue = terrainNoise.GetNoise(worldX, worldZ);

        float terrainHeight = noiseValue * biome.TERRAIN_HEIGHT;
        int height = (int)(terrainHeight + biome.TERRAIN_MIN_HEIGHT);

        if (y > height)
            return 0;

        if (y == height)
            voxel = biome.surfaceBlock;
        else if (height - biome.subsurfaceHeight < y)
            voxel = biome.subsurfaceBlock;
        else
            voxel = 2; // Stone

        return voxel;
    }
};