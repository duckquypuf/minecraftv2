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
        while(!glfwWindowShouldClose(window.window))
        {
            window.processInput();
            player.processInput(window.getInput(), window.deltaTime);
            player.updateChunkCoord();

            if(lastPlayerCoord != player.coord)
            {
                lastPlayerCoord = player.coord;
            }

            std::cout << lastPlayerCoord.x << " | " << lastPlayerCoord.z << std::endl;

            world.updateRenderDistance(lastPlayerCoord);

            renderer.beginFrame();
            renderer.render(player.camera, &world, lastPlayerCoord);
            window.update();
        }
    }
};