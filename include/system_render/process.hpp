#ifndef __SYSTEM_RENDER_PROCESS_HPP__
#define __SYSTEM_RENDER_PROCESS_HPP__

#include "../system.hpp"
#include "../text_area.hpp"
#include "render/render.hpp"

namespace SystemRender{

class Process : virtual private Utility::TextArea, public virtual Render::Widget{
private:
	const Sys::Process& _proc;
public:
	Process(const Sys::Process& proc);

	void render(Render::Buffer& b) override;
};
}


#endif
