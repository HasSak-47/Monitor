#include <progress_bar.hpp>

using namespace Utility;

void ProgressBar::render(Render::Buffer& buf){
    bool ends = ((int)this->opts & (int)Opts::Ends) != 0;
    size_t len = buf.get_width() - 2 * ends; 
	size_t max = size_t(this->per * len);
    size_t min = ends ? 1 : 0;
	if(ends){
		buf.get(0, 0).chr = '[';
		buf.get(len - 1, 0).chr = ']';
	}
    for(size_t i = 0; i < max; ++i){
		Render::Unit& v = buf.get(i + min, 0);
        v.chr = this->var_char;
        v.col = this->colors;
    }
    for(size_t i = max; i < len - 1 * ends; ++i){
		Render::Unit& v = buf.get(i, 0);
        v.chr = ' ';
        v.col = this->colors;
    }
}

