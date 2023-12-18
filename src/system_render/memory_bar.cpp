#include <iostream>

#include <system_render/memory_bar.hpp>
#include <progress_bar.hpp>

MemoryBar::MemoryBar(size_t len):
    ProgressBar(len)
{
    self._used = ProgressBar(len, self.get_shared_buffer());
    self._buffers = ProgressBar(len, self.get_shared_buffer());
    self._shared = ProgressBar(len, self.get_shared_buffer());
    self._chached = ProgressBar(len, self.get_shared_buffer());
	self._chached.colors.foreground = Color::Yellow;
	self._buffers.colors.foreground = Color::Blue;
	self._shared.colors.foreground = Color::Magenta;
	self._used.colors.foreground = Color::Green;
}

#ifdef __DEBUG_MEM_BAR__
#endif


void MemoryBar::write(){
	self.get_buffer().clear();
    float total_cached = sys._cached_mem / float(sys._max_mem);
    float total_buffer = sys._buffer_mem / float(sys._max_mem);
    float total_free   = sys._free_mem   / float(sys._max_mem);
	float total_used   = 1. - total_free;

	self._chached.set_per(total_used);
	self._chached.write();
	self._buffers.set_per(total_used -= total_cached);
	self._buffers.write();
	self._used.set_per(total_used - total_buffer);
	self._used.write();
}

