#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "renderer.hpp"
#include <memory>


class ProgressBar : public Renderee{
private:
    size_t _len;
    Buffer _buffer;
    float _per;
public: 
    enum class Opts: uint8_t {
        Ends = 1,
    };
    Opts opts = Opts::Ends;
    char var_char = '|';

    ProgressBar(size_t len);

    void set_per(float p);
    void write() override;
    void bind(Window& window, size_t x, size_t y) override;
    void unbind(Window& window) override;
    Buffer& get_buffer() override;
};

#endif
