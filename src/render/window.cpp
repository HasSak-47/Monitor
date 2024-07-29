#include <curses.h>
#include <render/window.hpp>

using namespace Render;

Window::Window() {
	initscr();
	cbreak();
	noecho();

	int x = getmaxx(stdscr), y = getmaxy(stdscr);
	this->_render_buffer = Buffer(x, y);
}

Window::~Window(){
	endwin();
	cbreak();
	noecho();
}

void Window::render(){
	this->clear();
	for(auto& renderee : this->_renderees){
		renderee->write(this->_render_buffer);
	}


}
