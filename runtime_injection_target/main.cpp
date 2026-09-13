#include <cstdio>
#include <thread>
#include <chrono>

int i = 0;

int main() {

    while (true) {
        printf("hi%d\n", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        i++;
    }
}