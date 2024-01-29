#include <iostream>
#include <memory>
#include <render/render.hpp>

using namespace Render;

Slice::Slice(size_t len) : _slice(
	std::shared_ptr<Unit[]>(new Unit[len])
){
	this->_end = len;
}

Slice::Slice(const Slice& slice) : _slice(slice._slice){
	this->_beg = slice._beg;
	this->_end = slice._end;
}

Slice& Slice::operator=(const Slice& slice){
	this->_slice = slice._slice;
	this->_end = slice._end;
	this->_beg = slice._beg;

	return *this;
}

Slice Slice::get_subslice(size_t beg, size_t end){
	Slice new_slice = Slice(*this);
	new_slice._beg = beg;
	new_slice._end = end;

	return new_slice;
}

Unit& Slice::operator[](size_t index){
	return _slice[this->_beg + index];
}

Buffer::Buffer(size_t x, size_t y){
	this->_buffer = std::shared_ptr<Slice[]>(new Slice[y]);
	for(size_t i = 0; i < y; ++i){
		this->_buffer[i] = Slice(x);
	}
}

Unit& Buffer::get(size_t x, size_t y){
	return this->_buffer[y][x];
}
