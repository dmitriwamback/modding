//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_SHADER_H
#define RUNTIME_INJECTION_TARGET_SHADER_H
#include <glm/ext/matrix_float4x4.hpp>


class Shader {
public:
    Shader();
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    void Use();
    void SetMatrix4(const char* variableName, const glm::mat4& matrix);
    void SetVector3(const char* variableName, const glm::vec3& vector);

private:
    uint32_t program;
    int LoadShaderSource(const char* source, int type);
};


#endif //RUNTIME_INJECTION_TARGET_SHADER_H
