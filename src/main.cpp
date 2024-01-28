#include <curses.h>
#include <string>
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
	mut out_file = std::ofstream("../log_file.txt");
	mut logger = logs::Logger(std::move(out_file));

	mut window = Window();
	let size = window.get_size();

	mut mem_bar = SystemRender::MemoryBar(100);
	mut tst_bar = ProgressBar(100);

	mut timer = TextLine(10);

	mem_bar.bind(window, 0, 0);
	tst_bar.bind(window, 0, 1);
	timer.bind(window, size.x - 10, size.y - 1);
	size_t i = 0;
	while(window.get_char() != ' '){
		window.clear();
		timer.text = std::to_string(i++);
		tst_bar.set_per((i % 1001) / 1000.);
		window.render();
	}

	return 0;
}
