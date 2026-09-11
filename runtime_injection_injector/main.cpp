#include <iostream>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <dlfcn.h>
#include <cstring>
#include <vector>

#include "util/query_pid.h"

// Function to build shellcode for calling dlopen in the target process
static std::vector<uint32_t> buildDlopenShellcode(uint64_t pathAddr, uint64_t dlopenAddr) {
    std::vector<uint32_t> code;

    // The shellcode will perform the following steps:
    // 1. Move the address of the dylib path into x0 (first argument for dlopen)
    // 2. Move the RTLD_NOW flag (2) into x1 (second argument for dlopen)
    // 3. Move the address of dlopen into x9 (to call it)
    // 4. Branch to x9 to call dlopen
    auto emitMov64 = [&](int reg, uint64_t val) {
        code.push_back(0xD2800000 | reg | ((val & 0xFFFF) << 5));
        code.push_back(0xF2A00000 | reg | (((val >> 16) & 0xFFFF) << 5));
        code.push_back(0xF2C00000 | reg | (((val >> 32) & 0xFFFF) << 5));
        code.push_back(0xF2E00000 | reg | (((val >> 48) & 0xFFFF) << 5));
    };

    
    emitMov64(0, pathAddr); // Move path address into x0
    emitMov64(1, 2); // Move RTLD_NOW (2) into x1
    emitMov64(9, dlopenAddr); // Move dlopen address into x9
    code.push_back(0xD63F0120); // Branch to x9 (call dlopen)
    code.push_back(0x14000000);

    return code;
}

int main() {
    // List all current processes and print their names
    std::vector<ProcessInformation> processes = listCurrentProcesses();
    for (const auto& process : processes) {
        std::cout << process.name << std::endl;
    }
    printf("\n");

    // Find the PID of the target process by name
    std::string target = "runtime_injection_target";
    pid_t pid = findPidByName(target);

    // If the target process is not found, return an error
    if (pid == -1) {
        return -1;
    }
    std::cout << pid << std::endl;

    // Get the task port for the target process
    task_t task;
    kern_return_t kr = task_for_pid(mach_task_self(), pid, &task);
    if (kr != KERN_SUCCESS) {
        std::cout << "task_for_pid failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Allocate memory in the target process for the dylib path and write it
    const char* dylibPath = "/Users/dmitri/Documents/working/macho-runtime-injection/runtime_injection_injector/payload/payload.dylib";
    size_t pathLen = strlen(dylibPath) + 1;

    mach_vm_address_t remotePathAddr = 0; // Address in the target process where the dylib path will be written
    kr = mach_vm_allocate(task, &remotePathAddr, pathLen, VM_FLAGS_ANYWHERE); // Allocate memory in the target process

    if (kr != KERN_SUCCESS) {
        // If allocation fails, print an error message and return -1
        std::cout << "allocate path failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Write the dylib path into the allocated memory in the target process
    kr = mach_vm_write(task, remotePathAddr, (vm_offset_t)dylibPath, (mach_msg_type_number_t)pathLen);

    if (kr != KERN_SUCCESS) {
        std::cout << "write path failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Set the memory protection of the allocated memory to read-only
    void* localDlopenAddr = (void*)dlopen; // Get the address of dlopen in the local process
    auto shellcode = buildDlopenShellcode(remotePathAddr, (uint64_t)localDlopenAddr); // Build the shellcode to call dlopen in the target process

    // Allocate memory in the target process for the shellcode and write it
    mach_vm_address_t remoteCodeAddr = 0;
    size_t codeSize = shellcode.size() * sizeof(uint32_t);

    // Allocate memory in the target process for the shellcode
    kr = mach_vm_allocate(task, &remoteCodeAddr, codeSize, VM_FLAGS_ANYWHERE);
    if (kr != KERN_SUCCESS) {
        std::cout << "allocate code failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Write the shellcode into the allocated memory in the target process
    kr = mach_vm_write(task, remoteCodeAddr, (vm_offset_t)shellcode.data(), (mach_msg_type_number_t)codeSize);
    if (kr != KERN_SUCCESS) {
        std::cout << "write code failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Set the memory protection of the allocated memory for the shellcode to read and execute
    kr = mach_vm_protect(task, remoteCodeAddr, codeSize, FALSE, VM_PROT_READ | VM_PROT_EXECUTE);
    if (kr != KERN_SUCCESS) {
        std::cout << "protect code failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    
    mach_vm_address_t remoteStackAddr = 0; // Address in the target process where the stack will be allocated
    size_t stackSize = 16 * 1024; // 16KB
    kr = mach_vm_allocate(task, &remoteStackAddr, stackSize, VM_FLAGS_ANYWHERE); // Allocate memory in the target process for the stack
    kr = mach_vm_protect(task, remoteStackAddr, stackSize, FALSE, VM_PROT_READ | VM_PROT_WRITE);

    if (kr != KERN_SUCCESS) {
        std::cout << "allocate stack failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    // Set the memory protection of the allocated memory for the stack to read and write
    kr = mach_vm_protect(task, remoteStackAddr, stackSize, FALSE, VM_PROT_READ | VM_PROT_WRITE);

    // Calculate the top of the stack, ensuring it is aligned to a 16-byte boundary
    mach_vm_address_t stackTop = (remoteStackAddr + stackSize) & ~0xFULL;

    // Set up the thread state for the new thread in the target process
    arm_thread_state64_t threadState = {0};
    threadState.__pc = remoteCodeAddr;
    threadState.__sp = (remoteStackAddr + stackSize) & ~0xFULL;

    // Create a new thread in the target process that starts executing the shellcode
    thread_act_t remoteThread; // The thread_act_t variable to hold the reference to the newly created thread
    kr = thread_create_running(task, ARM_THREAD_STATE64, (thread_state_t)&threadState, ARM_THREAD_STATE64_COUNT, &remoteThread); // Create the thread in the target process

    if (kr != KERN_SUCCESS) {
        std::cout << "thread_create_running failed: " << mach_error_string(kr) << std::endl;
        return -1;
    }

    std::cout << "Injection triggered, check target's stdout for the dylib constructor output" << std::endl;
    return 0;
}