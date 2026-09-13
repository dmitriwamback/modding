//
// Created by Dmitri on 2026-09-13.
//

#include "Renderer.h"

#include <iostream>
#include <ostream>

#include "../shader/ShaderSources.h"

Camera Renderer::camera;

Renderer::Renderer() {
    shader = Shader();
    camera = Camera();
}

void Renderer::Initialize() {

    glfwInit();

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(1200, 800, "Target demonstration", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);

    for (int x = -10; x < 10; x++) {
        for (int z = -10; z < 10; z++) {

            Cube cube = Cube();
            cube.scale = glm::vec3(1.0f);
            cube.rotation = glm::vec3(0.0f);
            cube.position = glm::vec3(static_cast<float>(x) * 5.0f, 0.0f, static_cast<float>(z) * 5.0f);
            cube.Initialize();

            cubes.push_back(cube);
        }
    }

    shader = Shader(ShaderSources::DEFAULT_VERTEX_SHADER_SOURCE, ShaderSources::DEFAULT_FRAGMENT_SHADER_SOURCE);
    glfwSetCursorPosCallback(window, CursorPosCallback);
}

void Renderer::Loop() {

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glm::vec4 movement;
        movement.x = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ?  1.0f : 0.0f;
        movement.y = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? -1.0f : 0.0f;
        movement.z = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ?  1.0f : 0.0f;
        movement.w = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? -1.0f : 0.0f;

        float up   = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ?  1.0f : 0.0f;
        float down = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS ? -1.0f : 0.0f;

        camera.Update(movement, up, down, window);

        shader.Use();
        shader.SetMatrix4("projection", camera.projection);
        shader.SetMatrix4("lookAt", camera.lookAt);


        for (auto cube : cubes) {
            if (!cube.initialized) {
                cube.Initialize();
            }
            cube.Render(shader);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Renderer::CursorPosCallback(GLFWwindow *window, double xpos, double ypos) {

    if (glfwGetMouseButton(window, camera.mouseButton)) {
        float dy = ypos - camera.lastMouseY;
        float dx = xpos - camera.lastMouseX;

        camera.pitch -= dy * 0.005f;
        camera.yaw += dx * 0.005f;

        if (camera.pitch > 1.55f) camera.pitch = 1.55f;
        if (camera.pitch < -1.55f) camera.pitch = -1.55f;

        camera.lookDirection = glm::normalize(glm::vec3(cos(camera.yaw) * cos(camera.pitch), sin(camera.pitch), sin(camera.yaw) * cos(camera.pitch)));
    }

    camera.lastMouseX = xpos;
    camera.lastMouseY = ypos;
}
