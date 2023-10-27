#include <system_render.hpp>

MemoryBar::MemoryBar(size_t len):
    _bar(len)
{}

void MemoryBar::bind(Window& window, size_t x, size_t y) {
    window.bind_buffer(this, x, y);
}

void MemoryBar::unbind(Window& window) { _bar.unbind(window); }
Buffer & MemoryBar::get_buffer() {return this->_bar.get_buffer();}

void MemoryBar::write(){
    // poll system
    float p = 1.0 - sys._free_mem / float(sys._max_mem);

    _bar.set_per(p);
    _bar.write();
}
