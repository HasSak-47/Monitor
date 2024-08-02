// c/c++ stuff
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// unix stuff
#include <dirent.h>
#include <unistd.h>

// my stuff
#include <utils.hpp>
#include <system.hpp>


static bool is_process(struct dirent* file){
    if(file->d_type != DT_DIR)
        return false;

    // not efficient
    let len = strlen(file->d_name);
    char* name = file->d_name;
    if(std::all_of(name, name + len, isdigit))
        return true;

    return false;
}

using namespace Sys;

bool Process::func(){
    return self._functional;
}

bool Process::update(){
    mut stat_file  = std::ifstream(self._stat_path);
    mut statm_file = std::ifstream(self._statm_path);

    if(!stat_file.is_open() && !statm_file.is_open())
        return false;

    stat_file
        >> self._stat.pid;
    // i lov u c++ never change
    mut buf = ' ';
    while((buf = stat_file.get()) != EOF){
        if(buf == ')')
            break;
        if(buf != '(')
            self._stat.name += buf;
    }

    stat_file
        >> self._stat.state
        >> self._stat.parent_pid
        >> self._stat.group_id;

    statm_file
        >> self._statm.size
        >> self._statm.resident
        >> self._statm.shared
        >> self._statm.text
        >> self._statm.lib
        >> self._statm.data
        >> self._statm.dt;

    return true;
}

Process::Process(char* pid) {
    self._stat_path = std::string("/proc/") + pid + "/stat";
    self._statm_path = std::string("/proc/") + pid + "/statm";
    self.update();
}

const std::vector<Process>& System::get_processes(){
    DIR* dir = opendir("/proc");
    struct dirent* dirent;

    while(((dirent) = readdir(dir)) != nullptr){
        if(!is_process(dirent))
            continue;

        let pid = std::stoi(dirent->d_name);
        mut proc = std::find_if(self._process.begin(), self._process.end(),
            [&](Process& x){ return x._stat.pid == pid; }
        );

        if(proc != self._process.end()){
            let alive = proc->update();
            if(!alive)
                self._process.erase(proc);
        }
        else
            self._process.push_back(Process(dirent->d_name));
    }

    return self._process;
}

#include <iostream>
#include <map>

void System::update(){
    self.get_processes();
    std::ifstream file("/proc/meminfo");
    std::string name, type;
    std::map<std::string, size_t> map;
    size_t len;
    while(file >> name >> len >> type)
        map[name] = len;

    self._max_mem  = map["MemTotal:"];
    self._free_mem = map["MemFree:"];
    self._av_mem = map["MemAvailable:"];
    self._cached_mem = map["Cached:"];
    self._buffer_mem = map["Buffers:"];
}

System::System(){
    self.update();
}
