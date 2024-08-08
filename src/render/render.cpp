#include <algorithm>
#include <memory>
#include <render/render.hpp>
#include <stdexcept>

using namespace Render;

Slice::Slice(size_t len):
	_slice( std::shared_ptr<Unit[]>(new Unit[len]) ),
	_start(0),
	_end(len),
	_width(len)
{ // for (size_t i = 0; i < len; ++i) { this->_slice[i] = {' '}; }
}

Slice::Slice(const Slice& other):
	_slice( other._slice),
	_start(other._start),
	_end(other._end),
	_width(other._width)
{ }

Slice Slice::get_subslice(size_t start, size_t width){
	Slice copy = *this;
	copy._start = this->_start + start;
	copy._end   = std::min(this->_start + width, this->_end - 1);

	return copy;
}
Unit& Slice::get(size_t i){
	i += this->_start;
	if(i >= this->_width){
		throw std::runtime_error("i is bigger than width");
	}
	return this->_slice[i];
}

Buffer::Buffer(){}

Buffer::Buffer(size_t width, size_t height){
	this->_buffer.reserve(width);
	this->_width = width;
	this->_height = height;

	for(size_t i = 0; i < width; ++i){
		this->_buffer.push_back(Slice(height));
	}
}

void Buffer::clean(){
	for(size_t i = 0; i < this->_width; ++i){
		for(size_t j = 0; j < this->_height; ++j){
			this->get(i, j).chr = ' ';
			this->get(i, j).col = {1, 1, 1};
		}
	}

}

// static
Buffer Buffer::_init_empty(size_t width, size_t height){
	Buffer empty;
	empty._buffer.reserve(width);
	empty._width = width;
	empty._height = height;

	return empty; 
}

Unit& Buffer::get(size_t x, size_t y){
	if(x >= this->_width){
		throw std::runtime_error("x is bigger than width");
	}
	return this->_buffer[x].get(y);
}

Buffer Buffer::get_subbuffer(size_t x, size_t y, size_t w, size_t h){
	Buffer buf = Buffer::_init_empty(w, h);
	size_t max = std::min(x + w, this->get_width());

	for(size_t i = x; i < max; ++i){
		buf._buffer.push_back(this->_buffer[i].get_subslice(y, h));
	}
	return buf;
}

size_t Buffer::get_width(){ return this->_width; }
size_t Buffer::get_height(){ return this->_height; }

void Target::bind(std::shared_ptr<Widget> widget, size_t x, size_t y, size_t w, size_t h){
	this->_binds.push_back(WidgetBind{widget, x, y, w, h});
}
