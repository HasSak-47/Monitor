#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include <unistd.h>
#include <stdint.h>
#include <cstdint>
#include <vector>
#include <string>

namespace Sys{

class System;
class Process;

class Process{
public:
    struct _proc_stat{
        pid_t pid;
        std::string name;
        char state;
        pid_t parent_pid;
        pid_t group_id;
    };
    struct _proc_statm{
        size_t size;
        size_t resident;
        size_t shared;
        size_t text;
        size_t lib;
        size_t data;
        size_t dt;
    };
    _proc_stat  _stat;
    _proc_statm _statm;
    std::string _stat_path;
    std::string _statm_path;
    bool _functional = false;
    Process(char* pid);
    bool update();
    bool func();

    friend class System;
};

class System{
private:
    std::vector<Process> _process;
public:
    uint64_t _max_mem;
    uint64_t _free_mem;
    uint64_t _av_mem;

    uint64_t _cached_mem;
    uint64_t _buffer_mem;

    const std::vector<Process>& get_processes();
    System();
    void update();
};

extern System sys;

}

#endif // __PROCESS_HPP__
