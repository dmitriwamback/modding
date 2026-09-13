//
// Created by Dmitri on 2026-09-11.
//

#include <cstdio>
#include <dlfcn.h>
#include <unistd.h>

__attribute__((constructor))
static void injected() {
    printf("hello %d\n", getpid());
    
    int* iptr = reinterpret_cast<int*>(dlsym(RTLD_MAIN_ONLY, "i"));
    if (!iptr) {
        printf("failed to find 'i' in target process\n");
        return;
    }
    *iptr = 1000000;
}