#include <cstdio>
#include <thread>
#include <chrono>

int main() {
    int i = 0;

    while (true) {
        printf("hi%d\n", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        i++;
    }
}