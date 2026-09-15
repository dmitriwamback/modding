//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_EPA_H
#define RUNTIME_INJECTION_TARGET_EPA_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Simplex.h"
#include "../objects/Vertex.h"

struct Collision {
    glm::vec3 A, B, normal;
    float depth;
    bool collided;
};

class EPA {
public:
    static std::pair<std::vector<glm::vec4>, size_t> GetNormal(std::vector<glm::vec3>& polytope, std::vector<size_t> indices);
    static void AddUnique(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t A, size_t B);

    static Collision ApplyEPA(Simplex& simplex, std::vector<Vertex> vA, std::vector<Vertex> vB);
};


#endif //RUNTIME_INJECTION_TARGET_EPA_H
