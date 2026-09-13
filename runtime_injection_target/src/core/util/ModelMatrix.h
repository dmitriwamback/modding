//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_MODELMATRIX_H
#define RUNTIME_INJECTION_TARGET_MODELMATRIX_H
#include <glm/mat4x4.hpp>


class ModelMatrix {
public:
    static glm::mat4 CreateModelMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
};


#endif //RUNTIME_INJECTION_TARGET_MODELMATRIX_H
