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
    TextLine(size_t len);
    void write() override;
    Buffer& get_buffer() override;
};

#endif
