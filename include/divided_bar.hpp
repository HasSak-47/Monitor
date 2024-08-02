#ifndef __DIVIDED_BAR_HPP__
#define __DIVIDED_BAR_HPP__

#include <vector>

#include "progress_bar.hpp"
#include "render/render.hpp"

namespace Utility{

class DividedBar : public virtual Render::Widget {
private:
	std::vector<ProgressBar> _bars;
public:
	DividedBar() {}

	void add_section(ProgressBar bar);
	ProgressBar& get_section(size_t i);
	void render(Render::Buffer& buffer) override;
};

}

#endif

