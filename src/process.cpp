#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
  _pid = pid;
  CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long jiffies = LinuxParser::ActiveJiffies(_pid);
  long uptime = UpTime();
  _cpu = (((float)jiffies / sysconf(_SC_CLK_TCK)) / uptime);
  return _cpu;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(_pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(_pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return (a._cpu < _cpu);
}