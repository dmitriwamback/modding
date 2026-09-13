//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_RENDERER_H
#define RUNTIME_INJECTION_TARGET_RENDERER_H
#include <vector>

#include "../objects/Cube.h"
#include <GL/glew.h>
#include <glfw/glfw3.h>

#include "Camera.h"

class Renderer {
public:
    std::vector<Cube> cubes;
    static Camera camera;
    Shader shader;
    GLFWwindow* window;

    Renderer();
    void Initialize();
    void Loop();

private:
    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
};


#endif //RUNTIME_INJECTION_TARGET_RENDERER_H
