#ifndef _PROGRESS_BAR_HPP__
#define _PROGRESS_BAR_HPP__

#include "../render/render.hpp"

namespace Utility{

class ProgressBar : public virtual Render::Widget{
public: 
    enum class Opts: uint8_t {
        Ends = 1,

    };
    Opts opts = Opts::Ends;

	bool has_opt(Opts opts);

    char var_char = '|';
	Render::Color colors;
	float per = 0.;

    ProgressBar(){}
    ProgressBar(Render::Color col) : colors(col){}
	void render(Render::Buffer& buffer) override;
};

ProgressBar::Opts operator&(ProgressBar::Opts& a, ProgressBar::Opts& b);
ProgressBar::Opts operator|(ProgressBar::Opts& a, ProgressBar::Opts& b);
}

#endif
