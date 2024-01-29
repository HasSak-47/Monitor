#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "render/renderee.hpp"

class ProgressBar : public Render::Renderee{
private:
public: 
    enum class Opts: uint8_t {
        Ends = 1,
    };
    Opts opts = Opts::Ends;
    char var_char = '|';
	Render::Color colors;

    ProgressBar(){}

    void write(Render::Buffer& buffer) override;
};

#endif
