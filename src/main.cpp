#include <curses.h>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <fstream>

#include <logger.hpp>
#include <utils.hpp>
#include <system.hpp>
// #include <renderer.hpp>
#include <text_line.hpp>
#include <progress_bar.hpp>
#include <system_render/memory_bar.hpp>
#include "render/render.hpp"

namespace Sys{
	System sys;
}

using namespace Sys;

void delay(float seconds){
	std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
}

int main() {
	mut out_file = std::ofstream("../log_file.txt");
	mut logger = logs::Logger(std::move(out_file));

	return 0;
}
