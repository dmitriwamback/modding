//
// Created by Dmitri on 2026-09-11.
//

#include <cstdio>
#include <dlfcn.h>
#include <unistd.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <thread>

struct Vertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Cube {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool initialized = false;
    std::vector<Vertex> vertices;
    uint32_t vertexArrayObject;
    uint32_t vertexBufferObject;
};

struct Renderer {
    std::vector<Cube> cubes;
};

struct Camera {
    glm::vec3 position;
    glm::vec3 lookDirection;
    glm::vec3 upDirection;
    glm::mat4 projection;
    glm::mat4 lookAt;
    float yaw, pitch;
    float speed;
    float lastMouseX, lastMouseY;
    int mouseButton;
};

__attribute__((constructor))
static void injected() {
    printf("hello %d\n", getpid());

    std::thread([]() {
        // Attempt to find the renderer object in the target process using dlsym. The mangled name "renderer" corresponds to the global variable "renderer" in the target process.
        Renderer* renderer = reinterpret_cast<Renderer*>(dlsym(RTLD_MAIN_ONLY, "renderer"));

        // Attempt to find the camera object in the target process using dlsym. The mangled name "_ZN8Renderer6cameraE" corresponds to the member variable "camera" of the "Renderer" class.
        // To get the correct mangled name, you can use the command: `nm target_name | grep camera`.
        Camera* camera = reinterpret_cast<Camera*>(dlsym(RTLD_MAIN_ONLY, "_ZN8Renderer6cameraE"));

        // Check if the renderer and camera objects were found successfully. If not, print an error message and return early.
        if (!renderer) {
            std::cout << "renderer not found" << std::endl;
            return;
        }
        if (!camera) {
            std::cout << "camera not found" << std::endl;
            return;
        }

        while (true) {
            // Create a new cube object and initialize its properties based on the camera's position. The cube is positioned at the camera's location, with no rotation and a scale of 1.0 in all dimensions.
            Cube cube;
            cube.position = camera->position;
            cube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            cube.scale = glm::vec3(1.0f, 1.0f, 1.0f);
            cube.initialized = false;
            cube.vertexArrayObject = 0;
            cube.vertexBufferObject = 0;

            // Add the newly created cube to the renderer's list of cubes. This allows the renderer to manage and render the cube in the target process.
            renderer->cubes.push_back(cube);
            sleep(5); // Sleep for 5 seconds before adding the next cube to avoid overwhelming the renderer with too many cubes at once.
        }
    }).detach();
}