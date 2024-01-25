#include <curses.h>
#include <thread>
#include <fstream>

#include <logger.hpp>
#include <utils.hpp>
#include <system.hpp>
#include <renderer.hpp>
#include <text_line.hpp>
#include <progress_bar.hpp>
#include <system_render/memory_bar.hpp>

namespace Sys{
	System sys;
}

using namespace Sys;

void delay(float seconds){
	std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
}

int main() {
	mut out_file = std::ofstream("test_file.txt");
	mut logger = logs::Logger(std::move(out_file));

	logger.log("test string % % %\n", 1, 2.0 ,3);
	logger.log("test string");
}
