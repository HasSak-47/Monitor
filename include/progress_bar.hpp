#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "renderer.hpp"

class ProgressBar : public Renderee{
private:
    size_t _len;
    std::shared_ptr<Buffer> _buffer;

public: 
    ProgressBar(size_t len);

    void set_per(float p);
    void write() override;
    void bind(Window& window) override;
    void unbind(Window& window) override;
};

#endif
