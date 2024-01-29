/*
#include <memory>
#include <progress_bar.hpp>

ProgressBar::ProgressBar(size_t len): _len(len){
    self._buffer = std::make_shared<Buffer>(len);
}

ProgressBar::ProgressBar(size_t len, std::shared_ptr<Buffer> buffer): _len(len){
    self._buffer = buffer;
}

void ProgressBar::write(){
    let ends = ((int)self.opts & (int)Opts::Ends) != 0;
    let len = this->_len - 2 * ends; 
    mut max = size_t(this->_per * len);
    if(max > len)
        max = len;
    let min = ends ? 1 : 0;
    if(ends){
        self._buffer->get(0, 0).value()->c = '[';
        self._buffer->get(self._len - 1, 0).value()->c = ']';
    }
    for(size_t i = 0; i < max; ++i){
        mut& v = *self._buffer->get(i + min, 0).value();
        v.c = self.var_char;
        v.colors = self.colors;
    }
}

void ProgressBar::set_per(float per){
    this->_per = per;
}

Buffer& ProgressBar::get_buffer(){
    return *this->_buffer;
}

std::shared_ptr<Buffer> ProgressBar::get_shared_buffer(){
    return this->_buffer;
}
*/
