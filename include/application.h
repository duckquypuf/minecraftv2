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
    Player player = Player(&world, glm::vec3(CHUNK_WIDTH * WORLD_WIDTH / 2.0f, 100.0f, CHUNK_WIDTH * WORLD_WIDTH / 2.0f));

    void run()
    {
        while(!glfwWindowShouldClose(window.window))
        {
            window.processInput();
            player.processInput(window.getInput(), window.deltaTime);
            renderer.beginFrame();
            renderer.render(player.camera, &world);
            window.update();
        }
    }
};