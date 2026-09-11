//
// Created by Dmitri on 2026-09-11.
//

#ifndef RUNTIME_INJECTION_INJECTOR_QUERY_PID_H
#define RUNTIME_INJECTION_INJECTOR_QUERY_PID_H

#include <libproc.h>
#include <vector>
#include <string>
#include <cstdio>

// Structure to hold process information
struct ProcessInformation {
    pid_t pid;
    std::string name;
};

// Function to list all current processes and return their information
inline std::vector<ProcessInformation> listCurrentProcesses() {

    // Get the list of all current processes using proc_listpids and proc_name
    std::vector<ProcessInformation> activeProcesses;

    // Get the size of the buffer needed to hold all PIDs
    int bufferSize = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);
    if (bufferSize <= 0) {
        return activeProcesses;
    }

    // Allocate a buffer to hold the PIDs and retrieve them
    std::vector<pid_t> pids(bufferSize / sizeof(pid_t));

    // Get the actual number of PIDs retrieved
    int actualSize = proc_listpids(PROC_ALL_PIDS, 0, pids.data(), bufferSize);
    int count = actualSize / sizeof(pid_t);

    // Iterate through the retrieved PIDs and get their names using proc_name
    for (int i = 0; i < count; i++) {
        pid_t pid = pids[i];
        if (pid == 0) {
            continue;
        }

        // Get the name of the process corresponding to the PID
        char nameBuffer[PROC_PIDPATHINFO_MAXSIZE] = {0};
        int ret = proc_name(pid, nameBuffer, sizeof(nameBuffer));
    
        // If the process name is successfully retrieved, add it to the list of active processes
        if (ret > 0) {
            activeProcesses.push_back({pid, std::string(nameBuffer)});
        }
    }

    return activeProcesses;
}

// Function to find the PID of a process by its name
inline pid_t findPidByName(std::string name) {

    // List all current processes and check if any of them match the given name
    std::vector<ProcessInformation> activeProcesses = listCurrentProcesses();

    // Iterate through the list of active processes and return the PID if a match is found
    for (const auto& process : activeProcesses) {
        if (process.name == name) {
            return process.pid;
        }
    }

    // If no matching process is found, return -1 to indicate failure
    return -1;
}

#endif //RUNTIME_INJECTION_INJECTOR_QUERY_PID_H
