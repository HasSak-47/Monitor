#include "processor.h"
#include "linux_parser.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long idle = LinuxParser::Jiffies();
  long active = LinuxParser::ActiveJiffies();

  return 1.f - ((float)idle) / (active + idle);
};