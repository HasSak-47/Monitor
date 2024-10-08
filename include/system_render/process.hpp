#ifndef __SYSTEM_RENDER_PROCESS_HPP__
#define __SYSTEM_RENDER_PROCESS_HPP__

#include "../system.hpp"
#include "../widgets/table.hpp"
#include "../render/render.hpp"

namespace SystemRender{

class Process : virtual private Widgets::TextArea, public virtual Render::Widget{
private:
	const Sys::Process& _proc;
public:
	Process(const Sys::Process& proc);

	void render(Render::Buffer& b) override;
};

class Processes : virtual private Widgets::Table, public virtual Render::Widget {
private:
	std::vector<Sys::Process>& _ps;
public:
	Processes(std::vector<Sys::Process>& ps);

	void render(Render::Buffer& buf) override;
};

}

#endif
