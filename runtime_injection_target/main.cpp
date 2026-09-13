#include "src/core/scene/Renderer.h"

Renderer renderer;

int main() {
    renderer = Renderer();
    renderer.Initialize();
    renderer.Loop();
}