#include <progress_bar.hpp>

ProgressBar::ProgressBar(size_t len): _len(len){ }

void ProgressBar::write(){

}

void ProgressBar::bind(Window& window){
    this->_buffer = window.init_buffer(this, this->_len, 1);
}

void ProgressBar::unbind(Window& window){
}

void ProgressBar::set_per(float per){
    auto max = size_t(per * this->_len);
    if(max > this->_len) max = this->_len;
    for(size_t i = 0; i < max; ++i){
        this->_buffer->get(i, 0).value()->c = '|';
    }
}
