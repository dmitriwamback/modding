//
// Created by Dmitri on 2026-09-15.
//

#include "Simplex.h"

#include <glm/vec3.hpp>

Simplex& Simplex::operator=(std::initializer_list<glm::vec3> list) {
    for (auto v = list.begin(); v != list.end(); v++) {
        points[std::distance(list.begin(), v)] = *v;
    }
    simplexSize = list.size();
    return *this;
}

glm::vec3& Simplex::operator[](unsigned i) { return points[i]; }

void Simplex::PushFront(glm::vec3 point) {
    points = { point, points[0], points[1], points[2] };
    simplexSize = std::min(simplexSize + 1, 4);
}

unsigned Simplex::Size() const {
    return simplexSize;
}

const glm::vec<3, float> *Simplex::begin() const {
    return points.begin();
}

const glm::vec<3, float> *Simplex::end() const {
    return points.end() - (4 - simplexSize);
}
