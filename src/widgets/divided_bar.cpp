#include <widgets/divided_bar.hpp>
#include <render/render.hpp>
#include <stdexcept>
#include <sstream>

using namespace Widgets;

// badly made
void DividedBar::render(Render::Buffer& buf){
	size_t secs = this->_bars.size();
	for(size_t i = 0; i < secs; ++i){
		float b = this->_bars[i].per;
		for(size_t j = 1 + i; j < secs; j++){
			this->_bars[i].per += this->_bars[j].per;
		}
		this->_bars[i].render(buf);
		this->_bars[i].per = b;
	}
}


void DividedBar::add_section(ProgressBar bar){
	this->_bars.push_back(bar);
}

ProgressBar& DividedBar::get_section(size_t i){
	if(this->_bars.size() <= i){
		std::stringstream s;
		s << "error i (" << i << ") <= (" << this->_bars.size() << ")";
		throw std::runtime_error(s.str());
	}
	return this->_bars[i];
}
