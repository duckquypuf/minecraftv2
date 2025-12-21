#pragma once

#include <vector>
#include <glad/glad.h>

#include "world.h"

class ChunkMesh
{
public:
    ChunkMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    ~ChunkMesh()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void addBlockFaces(Chunk *chunk, World *world, int x, int y, int z, uint8_t blockID);

    void buildMesh(Chunk *chunk, World *world);

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

private:
    unsigned int VAO, VBO;
    int vertexCount = 0;

    std::vector<float> vertices;

    void addBlockFaces(Chunk chunk, World *world, int x, int y, int z, uint8_t blockID);

    void addFace(int faceIndex, int x, int y, int z)
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
        }
    }

    void upload()
    {
        vertexCount = vertices.size() / 8;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(float),
            vertices.data(),
            GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
};