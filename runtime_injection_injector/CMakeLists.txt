cmake_minimum_required(VERSION 4.3)
project(runtime_injection_injector)

set(CMAKE_CXX_STANDARD 20)

add_library(payload SHARED util/payload.cpp)

add_executable(runtime_injection_injector main.cpp
        util/query_pid.h)

find_package(glm REQUIRED)

target_link_libraries(runtime_injection_injector
    glm::glm
)