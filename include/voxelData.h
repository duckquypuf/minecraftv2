#pragma once

#include "block.h"
#include "FastNoiseLite.h"
#include "biome.h"

static inline FastNoiseLite biomeNoise;
static inline FastNoiseLite noise;
static inline FastNoiseLite terrainNoise;

static inline const Biome biomes[] =
{
    {"Plains", 1, 3, 4, 0.02f, 0.5f, 0.3f, 5, 1000, 64, 10},
    {"Desert", 6, 6, 3, 0.01f, 0.5f, 0.5f, 3, -500, 64, 5},
};

static inline const int CHUNK_WIDTH = 16;
static inline const int CHUNK_HEIGHT = 128;

static inline int RENDER_DISTANCE = 6;

static inline const int WORLD_WIDTH = 100;
static inline constexpr int HALF_WORLD_WIDTH = WORLD_WIDTH / 2;

static inline const float G = 36.1f;

static inline const Block blocks[] =
{
    {"Air", AIR, {0, 0, 0, 0, 0, 0}},
    {"Grass", SOLID, {1, 1, 1, 1, 0, 2}},
    {"Stone", SOLID, {3, 3, 3, 3, 3, 3}},
    {"Dirt", SOLID, {0, 0, 0, 0, 0, 0}},
    {"Oak Log", SOLID, {4, 4, 4, 4, 5, 5}},
    {"Oak Leaves", TRANSPARENT, {6, 6, 6, 6, 6, 6}},
    {"Sand", SOLID, {7, 7, 7, 7, 7, 7}},
};

static inline const float cubeVertices[6 * 6 * 8] = 
{
    // Back Front Left Right Bottom Top
 
    // Pos Normal TexCoord

    // BACK (0, 0, -1)
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,

    // FRONT (0, 0, 1)
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 0.0f,

    // LEFT (-1, 0, 0)
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 1.0f,

    // RIGHT (1, 0, 0)
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 0.0f,

     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 0.0f,

    // BOTTOM (0, -1, 0)
    -0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 1.0f,

    // TOP (0, 1, 0)
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 1.0f,
};

static inline const int faceChecks[6 * 3] =
{
    // Back Front Left Right Bottom Top

    // Back
    0, 0, -1,

    // Front
    0, 0, 1,

    // Left
    -1, 0, 0,

    // Right
    1, 0, 0,

    // Bottom
    0, -1, 0,

    // Top
    0, 1, 0,
};
