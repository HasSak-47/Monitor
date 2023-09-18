#include <curses.h>
#include <memory>
#include <renderer.hpp>

Buffer::Buffer(){}

Buffer::Buffer(size_t width, size_t height = 0):
    data(std::make_unique<Unit[]>(width * height)),
    _width(width),
    _height(height)
{}

Vector2<size_t> Buffer::size(){
    return Vector2{this->_width, this->_height};
}

Window::Window(){
    initscr();
    noecho();
    cbreak();
    start_color();

    size_t x {getmaxx(stdscr)};
    size_t y {getmaxy(stdscr)};

    this->_present_buffer = Buffer(x, y);

}

Window::~Window(){
    endwin();
}
