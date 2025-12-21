#pragma once

#include "window.h"
#include "renderer.h"
#include "world.h"
#include "camera.h"

class Application
{
public:
    Window window = Window("Minecraft Clone V2", 1440, 900);
    Renderer renderer = Renderer("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");
    World world;
    Camera camera;

    Application()
    {
        
    }

    void run()
    {
        while(!glfwWindowShouldClose(window.window))
        {
            window.processInput();
            camera.processInput(window.getInput(), window.deltaTime);
            renderer.beginFrame();
            renderer.render(camera, &world);
            window.update();
        }
    }
};