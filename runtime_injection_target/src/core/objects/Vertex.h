//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_VERTEX_H
#define RUNTIME_INJECTION_TARGET_VERTEX_H
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 uv;
};

#endif //RUNTIME_INJECTION_TARGET_VERTEX_H
