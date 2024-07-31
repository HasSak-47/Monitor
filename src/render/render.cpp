#include <algorithm>
#include <iostream>
#include <memory>
#include <render/render.hpp>

using namespace Render;

Slice::Slice(size_t len):
	_slice(std::make_unique<Unit[]>(len)),
	start(0),
	end(len),
	width(len)
{ }

Slice::Slice(const Slice& other):
	_slice( other._slice),
	start(other.start),
	end(other.end),
	width(other.width)
{ }

Slice Slice::get_subslice(size_t start, size_t width){
	Slice copy = *this;
	copy.start = this->start + start;
	copy.end   = std::min(this->start + width, this->end);

	return copy;
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

// static
Buffer Buffer::_init_empty(size_t width, size_t height){
	Buffer empty;
	empty._buffer.reserve(width);
	empty._width = width;
	empty._height = height;

	return empty; 
}

Unit& Buffer::get(size_t x, size_t y){
	return this->_buffer[y]._slice[x];
}

Buffer Buffer::get_subbuffer(size_t x, size_t y, size_t w, size_t h){
	Buffer buf = Buffer::_init_empty(w, h);
	for(size_t i = 0; i < h; ++i){
		buf._buffer.push_back(this->_buffer[i + y].get_subslice(x, h));
	}
	return buf;
}

size_t Buffer::get_width(){ return this->_width; }
size_t Buffer::get_height(){ return this->_height; }

void Target::bind(std::shared_ptr<Widget> widget, size_t x, size_t y, size_t w, size_t h){
	this->_binds.push_back(WidgetBind{widget, x, y, w, h});
}
