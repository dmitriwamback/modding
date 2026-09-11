//
// Created by Dmitri on 2026-09-11.
//

#include <cstdio>

extern "C" void injected() {
    printf("hello\n");
}