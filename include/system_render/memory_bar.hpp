#ifndef __SYSTEM_RENDER_MEMORY_BAR_HPP__
#define __SYSTEM_RENDER_MEMORY_BAR_HPP__

#include "../utils/divided_bar.hpp"
#include "../render/render.hpp"
#include "../system.hpp"

namespace SystemRender{

class MemoryBar : private Utility::DividedBar, virtual public Render::Widget{
private:
	Utility::DividedBar _bar;
	Sys::System sys;
	enum Sections {
		Cache = 0,
		Buffer = 1,
		Used = 2,
	};
public:
	MemoryBar();
	void render(Render::Buffer& buf) override;
};

}

#endif
