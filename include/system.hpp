#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <unistd.h>
#include <vector>

class Process{
private:
    pid_t _pid;
public:
    Process(pid_t pid);
};

class System{
private:
public:
    std::vector<Process> get_processes();
};

#endif // __PROCESS_HPP__
