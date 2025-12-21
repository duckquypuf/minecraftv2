#pragma once

#include "block.h"

static inline const int CHUNK_WIDTH = 5;
static inline const int CHUNK_HEIGHT = 5;

static inline const int WORLD_WIDTH = 1;

static inline const Block blocks[] =
{
    {"Air", AIR, {0, 0, 0, 0, 0, 0}},
    {"Grass", SOLID, {1, 1, 1, 1, 2, 0}},
};

static inline const float cubeVertices[6 * 6 * 8] = 
{
    // Back Front Left Right Bottom Top
 
    // Pos Normal TexCoord

    // BACK (0, 0, -1)
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

    // FRONT (0, 0, 1)
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f,  1.0f,   1.0f, 1.0f,

    // LEFT (-1, 0, 0)
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,   1.0f, 0.0f,

    // RIGHT (1, 0, 0)
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 1.0f,

     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,  0.0f,   1.0f, 1.0f,

    // BOTTOM (0, -1, 0)
    -0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f,-1.0f,  0.0f,   1.0f, 0.0f,

    // TOP (0, 1, 0)
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 0.0f,
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
