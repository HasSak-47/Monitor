#include <iostream>
#include <system_render/memory_bar.hpp>

using SystemRender::MemoryBar;

MemoryBar::MemoryBar() : DividedBar() {
	this->add_section(Utility::ProgressBar({1, 1, 0})); // cache
	this->add_section(Utility::ProgressBar({1, 0, 1})); // buffer
	this->add_section(Utility::ProgressBar({0, 1, 0})); // used
}

void MemoryBar::render(Render::Buffer& buf){
    float total_cached = this->sys._cached_mem / float(this->sys._max_mem);
    float total_buffer = this->sys._buffer_mem / float(this->sys._max_mem);
    float total_free   = this->sys._free_mem   / float(this->sys._max_mem);
	float total_used   = 1. - total_free;

	this->get_section(Cache).per = total_cached;
	this->get_section(Buffer).per = total_buffer;
	this->get_section(Used).per = total_used - (total_buffer + total_cached);
	(*this).DividedBar::render(buf);
}
