#include <algorithm>
#include <sstream>
#include <string>
#include <system_render/process.hpp>
#include <render/render.hpp>
#include <widgets/text_area.hpp>

using namespace SystemRender;

Process::Process(const Sys::Process& proc): Widgets::TextArea(0),_proc(proc) { }

void Process::render(Render::Buffer& buf){
	std::stringstream ss;
	ss << this->_proc._stat.pid << " " << this->_proc._stat.name << " "
		<< this->_proc.total() / 1000000 << " "
		;
	this->text = ss.str();
	this->Widgets::TextArea::render(buf);
}

Processes::Processes(std::vector<Sys::Process>& ps): Widgets::TextArea(0),_ps(ps) { }

void Processes::render(Render::Buffer& buf){
	size_t count = buf.get_height();
	size_t width = buf.get_width();

	std::sort(this->_ps.begin(), this->_ps.end(), [](const Sys::Process & a, const Sys::Process & b){
		return a.total() > b.total();
	});
	for(size_t i = 0; i < count; ++i){
		Process p = {this->_ps[i]};

		auto sub = buf.get_subbuffer(0, i, width, 1) ;
		p.render(sub);
	}
}
