#ifndef __TEXT_LINE_HPP__
#define __TEXT_LINE_HPP__

#include "renderer.hpp"
#include <string>

class TextLine : public Renderee{
private:
    Buffer _buffer;
    size_t _len;
public:
    std::string text;
    TextLine();
    void write() override;
    void bind(Window& window, size_t x, size_t y) override;
    void unbind(Window& window) override;
    Buffer& get_buffer() override;

};

#endif
