//
// Created by Dmitri on 2026-09-13.
//

#include "GJK.h"

bool GJK::SimplexLine(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 A = simplex[0];
    glm::vec3 B = simplex[1];

    glm::vec3 AB = B - A;
    glm::vec3 AO = -A;

    if (SameDirection(AB, AO)) {
        direction = glm::cross(glm::cross(AB, AO), AO);
    }
    else {
        simplex = { A };
        direction = AO;
    }

    return false;
}

bool GJK::SimplexTriangle(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 A = simplex[0];
    glm::vec3 B = simplex[1];
    glm::vec3 C = simplex[2];

    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    glm::vec3 AO = -A;

    glm::vec3 ABC = glm::cross(AB, AC);

    if (SameDirection(glm::cross(ABC, AC), AO)) {
        if (SameDirection(AC, AO)) {
            simplex = { A, C };
            direction = glm::cross(glm::cross(AC, AO), AC);
        }
        else {
            return SimplexLine(simplex = {A, B}, direction);
        }
    }
    else {
        if (SameDirection(glm::cross(AB, ABC), AO)) {
            return SimplexLine(simplex = {A, B}, direction);
        }

        if (SameDirection(ABC, AO)) {
            direction = ABC;
        }
        else {
            simplex = { A, C, B };
            direction = -ABC;
        }
    }

    return false;
}

bool GJK::SimplexTetrahedron(Simplex &simplex, glm::vec3 &direction) {

    glm::vec3 A = simplex[0];
    glm::vec3 B = simplex[1];
    glm::vec3 C = simplex[2];
    glm::vec3 D = simplex[3];

    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    glm::vec3 AD = D - A;
    glm::vec3 AO = -A;

    glm::vec3 ABC = glm::cross(AB, AC);
    glm::vec3 ACD = glm::cross(AC, AD);
    glm::vec3 ADB = glm::cross(AD, AB);

    if (SameDirection(ABC, AO)) {
        return SimplexTriangle(simplex = {A, B, C}, direction);
    }
    if (SameDirection(ACD, AO)) {
        return SimplexTriangle(simplex = {A, C, D}, direction);
    }
    if (SameDirection(ADB, AO)) {
        return SimplexTriangle(simplex = {A, D, B}, direction);
    }

    return true;
}

bool GJK::HandleSimplex(Simplex &simplex, glm::vec3 &direction) {

    switch (simplex.Size()) {
        case 2:
            return SimplexLine(simplex, direction);
        case 3:
            return SimplexTriangle(simplex, direction);
        case 4:
            return SimplexTetrahedron(simplex, direction);
    }
    return false;
}

bool GJK::SameDirection(glm::vec3 direction, glm::vec3 &AO) {
    return glm::dot(direction, AO) > 0;
}

glm::vec3 GJK::GetFurthestPoint(std::vector<glm::vec3>& vertices, glm::vec3 direction) {
    glm::vec3 max = vertices[0];
    float dstMax = glm::dot(max, direction);

    for (const glm::vec3& vertex : vertices) {
        float dst = glm::dot(vertex, direction);

        if (dst > dstMax) {
            dstMax = dst;
            max = vertex;
        }
    }

    return max;
}

glm::vec3 GJK::Support(const std::vector<Vertex> &vertices, const glm::vec3 &direction) {
    std::vector<glm::vec3> v;

    for (int i = 0; i < vertices.size(); i++) {
        const glm::vec3& vertex = vertices[i].vertex;
        v.push_back(vertex);
    }
    return GetFurthestPoint(v, direction);
}

Collision GJK::Collide(Cube A, Cube B) {
    std::vector<Vertex> vA = A.ProjectedVertices();
    std::vector<Vertex> vB = B.ProjectedVertices();

    Collision collisionInfo{};
    collisionInfo.collided = false;

    glm::vec3 support = Support(vA, glm::vec3(1.0f, 0.0f, 0.0f)) - Support(vB, -glm::vec3(1.0f, 0.0f, 0.0f));

    Simplex simplex = Simplex();
    simplex.PushFront(support);

    glm::vec3 direction = -support;

    for (int i = 0; i < 10; i++) {
        glm::vec3 supportA = Support(vA,  direction);
        glm::vec3 supportB = Support(vB, -direction);
        support = supportA - supportB;

        if (glm::dot(support, direction) <= 0.0f) {
            return collisionInfo;
        }

        simplex.PushFront(support);

        if (HandleSimplex(simplex, direction)) {
            collisionInfo.collided = true;
            return collisionInfo;
        }
    }

    return collisionInfo;
}
