#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "render/render.hpp"

namespace Utility{
class ProgressBar : public Render::Widget{
public: 
    enum class Opts: uint8_t {
        Ends = 1,
    };
    Opts opts = Opts::Ends;
    char var_char = '|';
	Render::Color colors;
	float per = 0.;

    ProgressBar(){}
	void render(Render::Buffer& buffer) override;

};
}

#endif
