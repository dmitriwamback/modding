//
// Created by Dmitri on 2026-09-11.
//

#include <cstdio>
#include <unistd.h>

__attribute__((constructor))
static void injected() {
    printf("hello %d\n", getpid());
}