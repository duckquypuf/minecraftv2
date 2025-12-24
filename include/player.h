#pragma once

#include <glm/glm.hpp>

#include "camera.h"

class Player
{
public:
    glm::vec3 position;
    glm::vec3 velocity;

    Camera camera;
    World* world;

    ChunkCoord coord;

    bool paused = false;

    Player(World* _world, glm::vec3 _position)
    {
        world = _world;
        position = _position;
        velocity = glm::vec3(0.0f);

        camera.pos = position;

        updateChunkCoord();
    }

    void updateChunkCoord()
    {
        coord = ChunkCoord((int)(position.x / CHUNK_WIDTH), (int)(position.z / CHUNK_WIDTH));
    }

    void processInput(InputState state, float dt)
    {
        glm::vec3 forwardFlat = glm::normalize(glm::vec3(camera.forward.x, 0.0f, camera.forward.z));

        glm::vec3 inputDir = glm::vec3(0.0f);
        if (state.w)
            inputDir += forwardFlat;
        if (state.s)
            inputDir -= forwardFlat;
        if (state.a)
            inputDir -= camera.right;
        if (state.d)
            inputDir += camera.right;

        if(state.spacebar && isGrounded)
        {
            if(!jumpRequest)
            {
                velocity.y = jumpPower;
            }

            jumpRequest = true;
        } else
        {
            jumpRequest = false;
        }

        if (glm::length(inputDir) > 0.0f)
        {
            inputDir = glm::normalize(inputDir);
            velocity.x = inputDir.x * moveSpeed;
            velocity.z = inputDir.z * moveSpeed;
        }

        updateVelocity(dt);
    
        camera.processInput(state, dt);
    }

    void updateVelocity(float dt)
    {
        velocity.y -= G * dt;
        position.x += velocity.x * dt;

        if(checkCollision())
        {
            position.x -= velocity.x * dt;
            velocity.x = 0.0f;
        }

        position.y += velocity.y * dt;
        bool yCollision = checkCollision();
        if (yCollision)
        {
            position.y -= velocity.y * dt;

            isGrounded = (velocity.y < 0.0f);

            velocity.y = 0.0f;
        }
        else
        {
            isGrounded = false;
        }

        position.z += velocity.z * dt;

        if (checkCollision())
        {
            position.z -= velocity.z * dt;
            velocity.z = 0.0f;
        }

        camera.pos = position + glm::vec3(0.0f, playerHeight, 0.0f);

        if(isGrounded)
        {
            velocity.x -= velocity.x * groundFriction * dt;
            velocity.z -= velocity.z * groundFriction * dt;
        } else
        {
            velocity.x -= velocity.x * airResistance * dt;
            velocity.z -= velocity.z * airResistance * dt;
        }
    }

private:
    float moveSpeed = 5.0f;
    float jumpPower = 10.0f;

    float playerWidth = 0.4f;
    float playerHeight = 1.8f;

    float groundFriction = 10.0f;
    float airResistance = 2.0f;

    bool isGrounded = false;
    bool jumpRequest = false;

    bool checkCollision()
    {
        float halfWidth = playerWidth / 2.0f;

        // Check corners of player bounding box
        glm::vec3 checkPoints[] = {
            // Bottom corners
            position + glm::vec3(-halfWidth, 0.0f, -halfWidth),
            position + glm::vec3(halfWidth, 0.0f, -halfWidth),
            position + glm::vec3(-halfWidth, 0.0f, halfWidth),
            position + glm::vec3(halfWidth, 0.0f, halfWidth),

            // Top corners
            position + glm::vec3(-halfWidth, playerHeight, -halfWidth),
            position + glm::vec3(halfWidth, playerHeight, -halfWidth),
            position + glm::vec3(-halfWidth, playerHeight, halfWidth),
            position + glm::vec3(halfWidth, playerHeight, halfWidth),

            // Middle corners
            position + glm::vec3(-halfWidth, playerHeight * 0.5f, -halfWidth),
            position + glm::vec3(halfWidth, playerHeight * 0.5f, -halfWidth),
            position + glm::vec3(-halfWidth, playerHeight * 0.5f, halfWidth),
            position + glm::vec3(halfWidth, playerHeight * 0.5f, halfWidth),
        };

        for (const auto &point : checkPoints)
        {
            if (world->isVoxelSolid(round(point.x), round(point.y), round(point.z)))
            {
                return true;
            }
        }

        return false;
    }
};