#include <iostream>

#include <system_render.hpp>
#include <progress_bar.hpp>


MemoryBar::MemoryBar(size_t len):
    ProgressBar(len)
{
    self._used = ProgressBar(len, self.get_shared_buffer());
    self._buffers = ProgressBar(len, self.get_shared_buffer());
    self._shared = ProgressBar(len, self.get_shared_buffer());
    self._chached = ProgressBar(len, self.get_shared_buffer());
    self._chached.color = UnitColor {
        {0,0,0,0},
        {255,255,0,0},
    };
}

#ifdef __DEBUG_MEM_BAR__
#endif


void MemoryBar::write(){
    float total_cached = sys._cached_mem / float(sys._max_mem);
    float total_buffer = sys._buffer_mem / float(sys._max_mem);
    float total_free   = sys._free_mem   / float(sys._max_mem);
    float total_av     = sys._av_mem     / float(sys._max_mem);
}
