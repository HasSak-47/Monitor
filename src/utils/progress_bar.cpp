#include <utils/progress_bar.hpp>

using namespace Utility;


void ProgressBar::render(Render::Buffer& buf){
    bool ends = this->has_opt(Opts::Ends);
    size_t len = buf.get_width() - 2 * ends; 
	float p = this->per;
	if(p > 1)
		p = 1;
	if(p < 0)
		p = 0;

	size_t max = (size_t)(len * p);
    size_t min = ends ? 1 : 0;
	if(ends){
		buf.get(0, 0).chr = '[';
		buf.get(len + 1, 0).chr = ']';
	}
    for(size_t i = 0; i < max; ++i){
		Render::Unit& v = buf.get(i + min, 0);
        v.chr = this->var_char;
		v.col = this->colors;
    }
}

using Opts = ProgressBar::Opts;

bool ProgressBar::has_opt(Opts a){
	return (int)a != 0;
}

Opts operator&(Opts& a, Opts& b){
	return (Opts)((int)a & (int)b);
}

Opts operator|(Opts& a, Opts& b){
	return (Opts)((int)a & (int)b);
}
