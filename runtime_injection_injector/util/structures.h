#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Vertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Shader {
    uint32_t program;
};

struct Cube {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool initialized = false;
    std::vector<Vertex> vertices;
    uint32_t vertexArrayObject;
    uint32_t vertexBufferObject;
};

struct Renderer {
    std::vector<Cube> cubes;
    Shader shader;
    GLFWwindow* window;
};

struct Camera {
    glm::vec3 position;
    glm::vec3 lookDirection;
    glm::vec3 upDirection;
    glm::mat4 projection;
    glm::mat4 lookAt;
    float yaw, pitch;
    float speed;
    float lastMouseX, lastMouseY;
    int mouseButton;
};