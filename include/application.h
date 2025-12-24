#pragma once

#include "voxelData.h"
#include "window.h"
#include "renderer.h"
#include "world.h"
#include "player.h"

class Application
{
public:
    Window window = Window("Minecraft Clone V2", 1440, 900);
    Renderer renderer = Renderer("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");
    World world;
    Player player = Player(&world, glm::vec3(CHUNK_WIDTH * HALF_WORLD_WIDTH, 100.0f, CHUNK_WIDTH * HALF_WORLD_WIDTH));

    ChunkCoord lastPlayerCoord;

    void run()
    {
        world.generateChunks();

        uint8_t frames = 0;

        while(!glfwWindowShouldClose(window.window))
        {
            window.processInput();
            
            if(frames > 1)
            {
                player.processInput(window.getInput(), window.deltaTime);
                player.updateChunkCoord();
            } else {
                frames++;
            }

            std::cout << player.position.y << std::endl;

            if(lastPlayerCoord != player.coord)
            {
                lastPlayerCoord = player.coord;
            }

            world.updateRenderDistance(lastPlayerCoord);

            renderer.beginFrame();
            renderer.render(player.camera, &world, lastPlayerCoord);
            window.update();
        }
    }
};