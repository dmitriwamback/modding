//
// Created by Dmitri on 2026-09-15.
//

#ifndef RUNTIME_INJECTION_TARGET_SIMPLEX_H
#define RUNTIME_INJECTION_TARGET_SIMPLEX_H
#include <array>
#include <glm/vec3.hpp>


class Simplex {
public:
    Simplex() = default;

    Simplex& operator=(std::initializer_list<glm::vec3> list);
    glm::vec3& operator[](unsigned int i);

    void PushFront(glm::vec3 point);
    unsigned Size() const;

    const glm::vec<3, float> *begin() const;

    const glm::vec<3, float> *end() const;

private:
    std::array<glm::vec3, 4> points;
    int simplexSize;
};


#endif //RUNTIME_INJECTION_TARGET_SIMPLEX_H
