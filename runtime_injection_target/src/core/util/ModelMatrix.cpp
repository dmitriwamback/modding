//
// Created by Dmitri on 2026-09-13.
//

#include "ModelMatrix.h"

#include <glm/ext/matrix_transform.hpp>

#include "MathUtil.h"


glm::mat4 ModelMatrix::CreateModelMatrix(const glm::vec3 &positionVec, const glm::vec3 &rotationVec, const glm::vec3 &scaleVec) {

    glm::mat4 position = glm::translate(glm::mat4(1.0f), positionVec);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), scaleVec);
    glm::mat4 rotation = MathUtil::CreateRotationMatrix(rotationVec);

    return position * rotation * scale;
}
