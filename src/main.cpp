#include <curses.h>
#include <string>
#include <thread>
#include <iostream>

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
    mut window = Window();
	SystemRender::MemoryBar bar(100);
	bar.bind(window, 0, 0);

	for(size_t i = 0; i <= 100; ++i){
		window.render();
		delay(0.1);
	}
}
