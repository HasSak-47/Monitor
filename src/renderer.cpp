#include <curses.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <optional>
#include <renderer.hpp>

Color::Color(size_t id): color_id(id){}
Color::Color(): color_id(0){}

const Color Color::Black(0);
const Color Color::Red(1);
const Color Color::Green(2);
const Color Color::Yellow(3);
const Color Color::Blue(4);
const Color Color::Cyan(5);
const Color Color::Magenta(6);
const Color Color::White(7);

std::vector<size_t> UnitColor::_colors;

size_t Color::get_color(){
	return this->color_id;
}

const Unit Unit::default_unit = {
	{ Color::White, Color::Black, },
	' '
};

void UnitColor::set_color(){
	let f = self.foreground.get_color();
	let b = self.background.get_color();
	attron(COLOR_PAIR(b * 8 + f));
}

void UnitColor::unset_color(){
	let f = self.foreground.get_color();
	let b = self.foreground.get_color();
	attroff(COLOR_PAIR(b * 8 + f));
}

void UnitColor::init_color(){
}

UnitColor::UnitColor(Color fg, Color bg):
	foreground(fg),
	background(bg)
{
	init_color();
}

UnitColor::UnitColor(): UnitColor(Color::White, Color::Black) { }

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
    start_color();
	// this is a hack
	for(size_t ij = 0; ij < 64; ++ij){
		let i = ij % 8;
		let j = ij / 8;
		init_pair(ij, i, j);
	}

    noecho();
    cbreak();
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
			UnitColor(Color::White).set_color();
            if(isprint(val->c)){
				val->colors.set_color();
                mvaddch(j, i, val->c);
            }
        }
    refresh();
}

Vector2<size_t> Window::get_size() {
    return this->_present_buffer.size();
}


void Buffer::clear(){
    for(size_t i = 0; i < _width * _height; ++i)
        this->data[i] = Unit::default_unit;
}
