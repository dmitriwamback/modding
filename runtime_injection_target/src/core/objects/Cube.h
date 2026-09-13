//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_CUBE_H
#define RUNTIME_INJECTION_TARGET_CUBE_H

#include <glm/vec3.hpp>
#include "Vertex.h"
#include "../shader/Shader.h"

class Cube {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool initialized = false;

    std::vector<Vertex> vertices;

    void Initialize();
    void Render(Shader& shader);

private:
    uint32_t vertexArrayObject = 0;
    uint32_t vertexBufferObject = 0;
};


#endif //RUNTIME_INJECTION_TARGET_CUBE_H
