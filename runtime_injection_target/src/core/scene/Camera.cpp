//
// Created by Dmitri on 2026-09-13.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    position = glm::vec3(0.0f, 6.0f, 0.0f);
    lookDirection = glm::vec3(0.0f, 0.0f, 1.0f);

    projection = glm::perspective(3.14159265358f/2.0f, 3.0f/2.0f, 0.1f, 1000.0f);
    upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::CalculateVelocity(glm::vec4 movement, float up, float down) const {

    float forward   = movement.x,
          backward  = movement.y,
          left      = movement.z,
          right     = movement.w;

    glm::vec3 motion = lookDirection;
    glm::vec3 rightMotion = glm::normalize(glm::cross(motion, upDirection));

    float forwardMotion  = forward + backward,
          sidewaysMotion = left + right,
          verticalMotion = up + down;

    glm::vec3 vStraight = motion * forwardMotion * speed;
    glm::vec3 vRight    = rightMotion * sidewaysMotion * speed;
    glm::vec3 vUp       = upDirection * verticalMotion * speed;

    return vStraight - vRight + vUp;
}

void Camera::Update(glm::vec4 movement, float up, float down, GLFWwindow* window) {
    glm::vec3 velocity = CalculateVelocity(movement, up, down);
    position += velocity;

    lookDirection = glm::normalize(glm::vec3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)));
    lookAt = glm::lookAt(position, position + lookDirection, upDirection);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float)width / (float)height;

    projection = glm::perspective(3.14159265358f / 2.0f, aspect, 0.1f, 1000.0f);
}

void Camera::UpdateLookAtMatrix() {
    lookAt = glm::lookAt(position, position + lookDirection, upDirection);
}
