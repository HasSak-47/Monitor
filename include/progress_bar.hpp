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
    std::shared_ptr<Buffer> _buffer;
    std::shared_ptr<float> _per;
public: 
    Opts opts = (Opts)3;
    ProgressBar(size_t len);
    char var_char = '|';

    void set_per(float p);
    void write() override;
    void bind(Window& window) override;
    void unbind(Window& window) override;
};

#endif
