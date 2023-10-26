#include <algorithm>
#include <cctype>
#include <fstream>
#include <system.hpp>
#include <dirent.h>
#include <unistd.h>
#include <optional>
#include <string>
#include <cstring>
#include <utils.hpp>

static std::optional<pid_t> get_pid(struct dirent* file){
    if(file->d_type != DT_DIR)
        return std::nullopt;

    // not efficient
    let len = strlen(file->d_name);
    char* name = file->d_name;
    if(!std::all_of(name, name + len, isdigit))
        return std::nullopt;

    return std::stoi(name);
}

Process::Process(pid_t pid): _pid(pid){ }

std::vector<Process> System::get_processes(){
    DIR* dir = opendir("/proc");
    struct dirent* file;

    std::vector<Process> processes = {};
    while(((file) = readdir(dir)) != nullptr){
        auto pid = get_pid(file);
        if(pid.has_value())
            processes.push_back( Process(pid.value()) );
    }

    return processes;
}

#include <iostream>
#include <map>

void System::refresh(){
    std::ifstream file("/proc/meminfo");
    std::string name, type;
    std::map<std::string, size_t> map;
    size_t len;
    while(file >> name >> len >> type)
        map[name] = len;

    _max_mem  = map["MemTotal:"];
    _free_mem = map["MemFree:"];
}

System::System(){
    self.refresh();
}
