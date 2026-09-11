#include <cstdio>
#include <thread>
#include <chrono>

int main() {
    while (true) {
        printf("hi\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}