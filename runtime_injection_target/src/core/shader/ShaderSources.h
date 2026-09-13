//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_SHADERSOURCES_H
#define RUNTIME_INJECTION_TARGET_SHADERSOURCES_H


class ShaderSources {
public:
    static constexpr const char* DEFAULT_VERTEX_SHADER_SOURCE = R"(
        #version 410 core

        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 inNormal;
        layout (location = 2) in vec2 uv;

        uniform mat4 projection;
        uniform mat4 lookAt;
        uniform mat4 model;

        out vec3 normal;
        out vec3 fragp;

        void main() {
            normal = transpose(inverse(mat3(model))) * inNormal;
            fragp = (model * vec4(position, 1.0)).xyz;
            gl_Position = projection * lookAt * vec4(fragp, 1.0);
        }
    )";

    static constexpr const char* DEFAULT_FRAGMENT_SHADER_SOURCE = R"(
        #version 410 core

        in vec3 normal;
        in vec3 fragp;

        out vec4 fragc;
        vec3 lightPosition = vec3(10000.0, 30000.0, 20000.0);
        vec3 color = vec3(1.0);

        void main() {
            vec3 lightDir = normalize(lightPosition - fragp);
            float diff = max(dot(normal, lightDir), 0.0);
            vec3 diffuse = vec3(1.0) * diff;

            vec3 ambient = color * 0.2;

            fragc = vec4(diffuse + ambient, 1.0);
        }
)";
};


#endif //RUNTIME_INJECTION_TARGET_SHADERSOURCES_H
