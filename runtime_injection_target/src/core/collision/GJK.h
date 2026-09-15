//
// Created by Dmitri on 2026-09-13.
//

#ifndef RUNTIME_INJECTION_TARGET_GJK_H
#define RUNTIME_INJECTION_TARGET_GJK_H

#include "EPA.h"
#include "Simplex.h"
#include "../objects/Cube.h"

class GJK {
public:
    static bool SimplexLine(Simplex& simplex, glm::vec3& direction);
    static bool SimplexTriangle(Simplex& simplex, glm::vec3& direction);
    static bool SimplexTetrahedron(Simplex& simplex, glm::vec3& direction);
    static bool HandleSimplex(Simplex& simplex, glm::vec3& direction);

    static bool SameDirection(glm::vec3 direction, glm::vec3& AO);
    static glm::vec3 GetFurthestPoint(std::vector<glm::vec3>& vertices, glm::vec3 direction);
    static glm::vec3 Support(const std::vector<Vertex>& vertices, const glm::vec3& direction);

    static Collision Collide(Cube A, Cube B);
    static Collision CollideCamera(Cube A);
};


#endif //RUNTIME_INJECTION_TARGET_GJK_H
