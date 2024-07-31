#include <curses.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>
#include <render/render.hpp>
#include <progress_bar.hpp>
#include <thread>

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

		for(auto& b : this->_binds){
			auto sub = this->_b.get_subbuffer(b.x, b.y, b.w, b.h);
			b.widget->render(sub);
		}

		for(size_t j = 0; j < _b.get_height(); ++j){
			for(size_t i = 0; i < _b.get_width(); ++i)
				std::cout << (char)_b.get(i, j).chr;
			std::cout << std::endl;
		}
		std::cout << "\r\e[" << _b.get_height() << "A";
		std::cout.flush();
	}

};

int main() {
	TemporyWindow win(50, 50);
	auto bar = std::make_shared<Utility::ProgressBar>();

	win.bind(bar, 0, 0, 50, 1);
	while(true){
		win.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}
