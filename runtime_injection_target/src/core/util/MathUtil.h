//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_MATHUTIL_H
#define RUNTIME_INJECTION_TARGET_MATHUTIL_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MathUtil {
public:
    static glm::mat4 CreateRotationMatrix(glm::vec3 rotation);
};


#endif //RUNTIME_INJECTION_TARGET_MATHUTIL_H
