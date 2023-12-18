#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "renderer.hpp"
#include <memory>


class ProgressBar : public Renderee{
private:
    std::shared_ptr<Buffer> _buffer;
    size_t _len;
    float _per;
public: 
    enum class Opts: uint8_t {
        Ends = 1,
    };
    Opts opts = Opts::Ends;
    char var_char = '|';
	UnitColor colors = UnitColor(Color::White);

    ProgressBar(size_t len);
    ProgressBar(size_t len, std::shared_ptr<Buffer> buffer);
    ProgressBar(){}

    void set_per(float p);
    void write() override;
    Buffer& get_buffer() override;

    std::shared_ptr<Buffer> get_shared_buffer() ;
};

#endif
