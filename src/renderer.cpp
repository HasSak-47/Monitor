#include <curses.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <optional>
#include <renderer.hpp>

Buffer::Buffer(){}

Buffer::Buffer(size_t width, size_t height):
    data(std::make_unique<Unit[]>(width * height)),
    _width(width),
    _height(height)
{}

Vector2<size_t> Buffer::size(){
    return Vector2{this->_width, this->_height};
}

size_t Buffer::len(){
    return this->_width * this->_height;
}

std::optional<Unit*> Buffer::get(size_t x, size_t y){
    size_t w = this->size().x;
    if(this->len() <= x + (y * w)){
        return {};
    }
    return &this->data[x + (y * w)];
}

Window::Window(){
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);

    size_t x {getmaxx(stdscr)};
    size_t y {getmaxy(stdscr)};

    this->_present_buffer = Buffer(x, y);
}


Window::~Window(){
    endwin();
}

void Window::bind_buffer(Renderee* parent, size_t x, size_t y){
    this->_renderees.push_back(Renderees{parent, {x, y}});
}

void Window::unbind_buffer(Renderee* parent){
    auto buffer = std::find_if(this->_renderees.begin(), this->_renderees.end(),
            [&](Renderees val){ return val.parent == parent; });
    if(buffer == this->_renderees.end()){
        std::cout << "parent not found!\n";
    }
    else{
        this->_renderees.erase(buffer);
    }
}

static void write_to_buffer(size_t x, size_t y, Buffer& dest, Buffer& src){
    auto s_size = src.size();

    for(size_t i = 0; i < s_size.x; ++i){
        for(size_t j = 0; j < s_size.y; ++j){
            auto dest_o = dest.get(i + x, j + y);
            auto  src_o =  src.get(i, j);
            if(dest_o.has_value() && src_o.has_value())
                *dest_o.value() = *src_o.value();
        }
    }
}

void Window::render(){
    for(mut& renderee : this->_renderees){
        renderee.parent->write();
        write_to_buffer(renderee.pos.x, renderee.pos.y, this->_present_buffer, renderee.parent->get_buffer());
    }

    auto psize = this->_present_buffer.size();
    for(size_t i = 0; i < psize.x; ++i)
        for(size_t j = 0; j < psize.y; ++j){
            let val = self._present_buffer.get(i, j).value();
            if(isprint(val->c)){
                let& bg = val->colors.background;
                let& fg = val->colors.foreground;
                // std::cout << "\x1b[38;2;"
                //     << fg.r << ','
                //     << fg.g << ','
                //     << fg.b;
                // std::cout << "\x1b[48;2;"
                //     << bg.r << ','
                //     << bg.g << ','
                //     << bg.b;
                mvaddch(j, i, val->c);
            }
        }
    refresh();
}

Vector2<size_t> Window::get_size() {
    return this->_present_buffer.size();
}

