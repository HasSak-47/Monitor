#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "renderer.hpp"
#include <memory>

enum class Opts: uint8_t {
    Ends = 1,
};

class ProgressBar : public Renderee{
private:
    size_t _len;
    Buffer _buffer;
    float _per;
public: 
    Opts opts = (Opts)3;
    ProgressBar(size_t len);
    char var_char = '|';

    void set_per(float p);
    void write() override;
    void bind(Window& window, size_t x, size_t y) override;
    void unbind(Window& window) override;
    Buffer& get_buffer() override;
};

#endif
