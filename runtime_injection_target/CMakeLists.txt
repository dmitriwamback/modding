cmake_minimum_required(VERSION 4.3)
project(runtime_injection_target)

set(CMAKE_CXX_STANDARD 20)

add_executable(runtime_injection_target main.cpp
        src/core/scene/Renderer.cpp
        src/core/scene/Renderer.h
        src/core/scene/Camera.cpp
        src/core/scene/Camera.h
        src/core/objects/Cube.cpp
        src/core/objects/Cube.h
        src/core/shader/Shader.cpp
        src/core/shader/Shader.h
        src/core/shader/ShaderSources.cpp
        src/core/shader/ShaderSources.h
        src/core/util/MathUtil.cpp
        src/core/util/MathUtil.h
        src/core/util/ModelMatrix.cpp
        src/core/util/ModelMatrix.h
        src/core/collision/GJK.cpp
        src/core/collision/GJK.h
        src/core/collision/EPA.cpp
        src/core/collision/EPA.h
        src/core/objects/Vertex.h)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(runtime_injection_target
    glfw
    GLEW::GLEW
    glm::glm
)