#ifndef __SYSTEM_RENDER_HPP__
#define __SYSTEM_RENDER_HPP__

#include "progress_bar.hpp"
#include "renderer.hpp"
#include "system.hpp"

class MemoryBar : public Renderee{
private:
    ProgressBar _bar;
public:
    MemoryBar(size_t len);

    void bind(Window& window, size_t x, size_t y) override;
    void unbind(Window& window) override;
    void write() override;
    Buffer & get_buffer() override;
};

#endif
