#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream mem_file(LinuxParser::kProcDirectory + "meminfo");
  string line, id;
  double memory[2];

  if(mem_file.is_open()){
    size_t index = 0;
    while(getline(mem_file, line)){
      std::istringstream mem_stream(line);
      mem_stream >> id >> memory[index++];
      if(id == "MemFree:") break;
    }
  }
  return 1.0 - (memory[1] / memory[0]);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream uptime_file(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
  long up_time = 0;
  if(uptime_file.is_open()){
    uptime_file >> up_time;
    uptime_file.close();
  }
  return up_time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

static int process_parser(string ID){
  std::ifstream processes_file(LinuxParser::kProcDirectory + "stat");
  string line, id;
  int value = 0;
  if(processes_file.is_open()){
    while(getline(processes_file, line)){
      std::istringstream proccesses_stream(line);
      proccesses_stream >> id >> value;
      if(ID == id) break;
    }
  }
  processes_file.close();
  return value;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  return process_parser("processes");
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  return process_parser("procs_running");
}

static string get_pid_status(int pid, string parameter){
  std::ifstream file(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  string id, line, data = "";
  
  if(file.is_open()){
    while(getline(file, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream status_stream(line);
      status_stream >> id >> data;
      if(id == parameter) break;
    }
  }

  return data;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  std::ifstream command_file(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string line;
  getline(command_file, line);
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string ram_used = get_pid_status(pid, "VmSize");
  return string(ram_used.begin(), ram_used.end() - 3);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  return get_pid_status(pid, "Uid");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, user_name = "NOT_FOUND", uid = get_pid_status(pid, "Uid");

  std::ifstream file(kPasswordPath);
  if(file.is_open()){
    while(getline(file, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::istringstream status_stream(line);
      string x, _uid;
      status_stream >> user_name >> x >> _uid;
      if(_uid == uid) break;
    }
  }

  return user_name;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
