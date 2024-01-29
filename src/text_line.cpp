/*
#include <algorithm>
#include <text_line.hpp>

TextLine::TextLine(size_t len): _len(len){
    self._buffer = std::make_shared<Buffer>(len);
}

void TextLine::write(){
    let max = std::min(self._len, self.text.size());
    for(size_t i = 0; i < max; ++i)
        self._buffer->get(i, 0).value()->c = self.text[i];
}
Buffer& TextLine::get_buffer(){
    return *self._buffer;
}
*/
