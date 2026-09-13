//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_CAMERA_H
#define RUNTIME_INJECTION_TARGET_CAMERA_H
#include <glfw/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


class Camera {
public:
    glm::vec3 position;
    glm::vec3 lookDirection;
    glm::vec3 upDirection;

    glm::mat4 projection, lookAt;

    float yaw = 0, pitch = 0;
    float speed = 0.5f;

    float lastMouseX, lastMouseY;
    int mouseButton = GLFW_MOUSE_BUTTON_RIGHT;

    Camera();

    void Update(glm::vec4 movement, float up, float down, GLFWwindow* window);
    void UpdateLookAtMatrix();

    glm::vec3 CalculateVelocity(glm::vec4 movement, float up, float down) const;
};


#endif //RUNTIME_INJECTION_TARGET_CAMERA_H
