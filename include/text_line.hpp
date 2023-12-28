#ifndef __TEXT_LINE_HPP__
#define __TEXT_LINE_HPP__

#include "renderer.hpp"
#include <memory>
#include <string>

class TextLine : public Renderee{
private:
	std::shared_ptr<Buffer> _buffer;
    size_t _len;
public:
    std::string text;
    TextLine(size_t len);
    TextLine(std::shared_ptr<Buffer> _buffer);
    void write() override;
    Buffer& get_buffer() override;
};

#endif
