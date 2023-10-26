#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <unistd.h>
#include <stdint.h>
#include <vector>
#include <string>

class Process{
private:
    pid_t _pid;
    std::string name = "";
public:
    Process(pid_t pid);
    void get_data();
};

class System{
public:
    uint64_t _max_mem;
    uint64_t _cached_mem;
    uint64_t _free_mem;
    std::vector<Process> get_processes();
    System();
    void refresh();
};

#endif // __PROCESS_HPP__
