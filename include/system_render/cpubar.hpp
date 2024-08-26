#ifndef __SYSTEM_RENDER_CPU_BAR_HPP__
#define __SYSTEM_RENDER_CPU_BAR_HPP__

#include "../render/render.hpp"
#include "../widgets/progress_bar.hpp"

namespace SystemRender{

class CPUBar : private Widgets::ProgressBar, virtual public Render::Widget{
private:
	Widgets::ProgressBar _bar;
public:
	CPUBar();
	void render(Render::Buffer& buf) override;
};

}

#endif
