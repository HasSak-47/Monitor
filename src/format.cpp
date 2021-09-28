#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
  int inter[3] = {};
  inter[2] = seconds % 60;
  inter[1] = (seconds / 60) % 60;
  inter[0] = (seconds / (60 * 60));
  string format;
  for(size_t i = 0; i < 3; ++i){
      if(inter[i] < 10) format += '0';
      format += std::to_string(inter[i]) + ':';
  }
  format.pop_back();
  return format;
}