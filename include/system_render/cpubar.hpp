#ifndef __SYSTEM_RENDER_CPU_BAR_HPP__
#define __SYSTEM_RENDER_CPU_BAR_HPP__

#include "../render/render.hpp"
#include "../widgets/divided_bar.hpp"

namespace SystemRender{

class CPUBar : private Widgets::DividedBar, virtual public Render::Widget{
public:
    size_t id = 0;
    bool render_text = true;
	CPUBar();
	void render(Render::Buffer& buf) override;
};

}

#endif
