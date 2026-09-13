//
// Created by Dmitri on 2026-09-13.
//

#include "Cube.h"

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "../util/ModelMatrix.h"

void Cube::Initialize() {
    initialized = true;

    vertices = {
        Vertex({-1.0f, -1.0f, -1.0f},  {0, 0, -1}, {0, 0}),
        Vertex({ 1.0f,  1.0f, -1.0f},  {0, 0, -1}, {1, 1}),
        Vertex({ 1.0f, -1.0f, -1.0f},  {0, 0, -1}, {1, 0}),
        Vertex({ 1.0f,  1.0f, -1.0f},  {0, 0, -1}, {1, 1}),
        Vertex({-1.0f, -1.0f, -1.0f},  {0, 0, -1}, {0, 0}),
        Vertex({-1.0f,  1.0f, -1.0f},  {0, 0, -1}, {0, 1}),

        Vertex({-1.0f, -1.0f,  1.0f},  {0, 0, 1}, {0, 0}),
        Vertex({ 1.0f, -1.0f,  1.0f},  {0, 0, 1}, {1, 0}),
        Vertex({ 1.0f,  1.0f,  1.0f},  {0, 0, 1}, {1, 1}),
        Vertex({ 1.0f,  1.0f,  1.0f},  {0, 0, 1}, {1, 1}),
        Vertex({-1.0f,  1.0f,  1.0f},  {0, 0, 1}, {0, 1}),
        Vertex({-1.0f, -1.0f,  1.0f},  {0, 0, 1}, {0, 0}),

        Vertex({-1.0f,  1.0f,  1.0f},  {-1, 0, 0}, {1, 1}),
        Vertex({-1.0f,  1.0f, -1.0f},  {-1, 0, 0}, {1, 0}),
        Vertex({-1.0f, -1.0f, -1.0f},  {-1, 0, 0}, {0, 0}),
        Vertex({-1.0f, -1.0f, -1.0f},  {-1, 0, 0}, {0, 0}),
        Vertex({-1.0f, -1.0f,  1.0f},  {-1, 0, 0}, {0, 1}),
        Vertex({-1.0f,  1.0f,  1.0f},  {-1, 0, 0}, {1, 1}),

        Vertex({ 1.0f,  1.0f,  1.0f},  {1, 0, 0}, {1, 1}),
        Vertex({ 1.0f, -1.0f, -1.0f},  {1, 0, 0}, {0, 0}),
        Vertex({ 1.0f,  1.0f, -1.0f},  {1, 0, 0}, {1, 0}),
        Vertex({ 1.0f, -1.0f, -1.0f},  {1, 0, 0}, {0, 0}),
        Vertex({ 1.0f,  1.0f,  1.0f},  {1, 0, 0}, {1, 1}),
        Vertex({ 1.0f, -1.0f,  1.0f},  {1, 0, 0}, {0, 1}),

        Vertex({-1.0f, -1.0f, -1.0f},  {0, -1, 0}, {0, 0}),
        Vertex({ 1.0f, -1.0f, -1.0f},  {0, -1, 0}, {1, 0}),
        Vertex({ 1.0f, -1.0f,  1.0f},  {0, -1, 0}, {1, 1}),
        Vertex({ 1.0f, -1.0f,  1.0f},  {0, -1, 0}, {1, 1}),
        Vertex({-1.0f, -1.0f,  1.0f},  {0, -1, 0}, {0, 1}),
        Vertex({-1.0f, -1.0f, -1.0f},  {0, -1, 0}, {0, 0}),

        Vertex({-1.0f,  1.0f, -1.0f},  {0, 1, 0}, {0, 0}),
        Vertex({ 1.0f,  1.0f,  1.0f},  {0, 1, 0}, {1, 1}),
        Vertex({ 1.0f,  1.0f, -1.0f},  {0, 1, 0}, {1, 0}),
        Vertex({ 1.0f,  1.0f,  1.0f},  {0, 1, 0}, {1, 1}),
        Vertex({-1.0f,  1.0f, -1.0f},  {0, 1, 0}, {0, 0}),
        Vertex({-1.0f,  1.0f,  1.0f},  {0, 1, 0}, {0, 1}),
    };

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertex));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Cube::Render(Shader &shader) {

    shader.Use();
    glm::mat4 model = ModelMatrix::CreateModelMatrix(position, rotation, scale);

    shader.SetMatrix4("model", model);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
