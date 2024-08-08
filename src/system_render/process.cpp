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

Processes::Processes(std::vector<Sys::Process>& ps): Widgets::Table({"pid", "name", "mem"}),_ps(ps) { }

void Processes::render(Render::Buffer& buf){
	std::sort(this->_ps.begin(), this->_ps.end(), [](const Sys::Process & a, const Sys::Process & b){
		return a.total() > b.total();
	});
	this->set_size(0, 5);
	this->set_size(2, 5);

	size_t height = buf.get_height();
	size_t offset = 0;

	for(size_t i = 0; i < height; ++i){
		this->set_col(i, {
			std::to_string(this->_ps[i]._stat.pid),
			this->_ps[i]._stat.name,
			std::to_string(this->_ps[i].total())
		});
	}

	this->Widgets::Table::render(buf);
}
