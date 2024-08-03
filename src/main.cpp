#include <sys/ioctl.h>

#include <iostream>
#include <memory>
#include <thread>

#include <widgets/text_area.hpp>
#include <render/render.hpp>
#include <widgets/progress_bar.hpp>
#include <widgets/divided_bar.hpp>
#include <system.hpp>
#include <system_render/memory_bar.hpp>
#include <system_render/process.hpp>

using namespace Render;

/*
 * this should not be used in the final prod!!!!
*/
class TemporyWindow : public Target{
private:
	Buffer _b;
public:
	TemporyWindow(size_t w, size_t h) : _b(w, h) { }

	void render() override {
		this->_b.clean();
		for(auto& b : this->_binds){
			auto sub = this->_b.get_subbuffer(b.x, b.y, b.w, b.h);
			b.widget->render(sub);
		}

		for(size_t j = 0; j < _b.get_height(); ++j){
			for(size_t i = 0; i < _b.get_width(); ++i){
				auto val = _b.get(i, j);

				std::cout << "\e[38;2;"
					<< (int)(val.col.r * 255) << ";"
					<< (int)(val.col.g * 255) << ";"
					<< (int)(val.col.b * 255) << "m" ;
				std::cout <<  (char)val.chr;
				std::cout << "\e[0m";
			}
			std::cout << std::endl;
		}
		std::cout << "\e[" << _b.get_height() << "A";
		std::cout.flush();
	}

};

int main() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	size_t width = w.ws_col / 2;
	size_t heigth= w.ws_row / 2;

	TemporyWindow win(width, heigth);
	Sys::System sys;

	auto bar = std::make_shared<SystemRender::MemoryBar>();
	auto procs = std::make_shared<SystemRender::Processes>(sys.get_processes());

	win.bind(bar, 0, 0, width, 1);
	win.bind(procs, 0, 1, width, heigth - 1);

	while(true){
		sys.update();
		win.render();

		using namespace std::chrono;
		std::this_thread::sleep_for(100ms);
	}

	return 0;
}
