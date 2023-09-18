#include <algorithm>
#include <cctype>
#include <system.hpp>
#include <dirent.h>
#include <unistd.h>
#include <optional>
#include <string>

static std::optional<pid_t> get_pid(struct dirent* file){
    if(file->d_type == 'd')
        return std::nullopt;

    // not efficient
    auto file_name = std::string(file->d_name);
    if(std::all_of(file_name.begin(), file_name.end(), isdigit))
        return std::nullopt;

    return std::stoi(file_name);
}

Process::Process(pid_t pid): _pid(pid){
}

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
