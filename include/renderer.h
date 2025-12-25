#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "stb_image.h"

#include "shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "camera.h"
#include "world.h"

#include "atlasGenerator.h"

class Renderer
{
public:
    unsigned int atlasTexture;

    Renderer(const char *vertPath, const char *fragPath)
    {
        std::cout << "Generating texture atlas..." << std::endl;
        bool success = AtlasGenerator::generateAtlas(
            "../textures/textures.json",
            "../textures",
            "../atlas/atlas_256x256.png");

        if (!success)
        {
            std::cerr << "WARNING: Atlas generation failed, using existing atlas if available" << std::endl;
        }

        shader = new Shader(vertPath, fragPath);

        // Load atlas from generated location
        atlasTexture = loadTexture("../atlas/atlas_256x256.png");
    }

    void beginFrame()
    {
        glClearColor(0.47f, 0.66f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void render(Camera cam, World *world, ChunkCoord &lastPlayerCoord)
    {
        shader->use();

        glm::mat4 view = cam.GetViewMatrix();
        glm::mat4 proj = cam.GetProjectionMatrix();

        shader->setMat4("view", view);
        shader->setMat4("projection", proj);

        // Render all chunks
        for (int x = lastPlayerCoord.x - RENDER_DISTANCE; x < lastPlayerCoord.x + RENDER_DISTANCE; x++)
        {
            for (int z = lastPlayerCoord.z - RENDER_DISTANCE; z < lastPlayerCoord.z + RENDER_DISTANCE; z++)
            {
                if (x < 0 || x >= WORLD_WIDTH || z < 0 || z >= WORLD_WIDTH)
                    continue;

                if (world->chunks[x][z]->mesh)
                {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(x * CHUNK_WIDTH, 0.0f, z * CHUNK_WIDTH));
                    shader->setMat4("model", model);
                    world->chunks[x][z]->mesh->draw();
                }
            }
        }
    }

private:
    Shader *shader;

    unsigned int loadTexture(const char *path)
    {
        if (!std::filesystem::exists(path))
        {
            std::cout << "ERROR: File does not exist at path: " << path << std::endl;
            return 0;
        }

        unsigned int id;
        glGenTextures(1, &id);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

        if (data)
        {
            std::cout << "Texture loaded successfully: " << width << "x" << height << " with " << nrComponents << " components" << std::endl;
            GLenum format;

            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "STB Image failed to load. Reason: " << stbi_failure_reason() << std::endl;
            std::cout << "Path attempted: " << path << std::endl;
            stbi_image_free(data);
            return 0;
        }
        return id;
    }
};