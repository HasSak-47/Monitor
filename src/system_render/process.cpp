#include <sstream>
#include <string>
#include <system_render/process.hpp>
#include "render/render.hpp"
#include "text_area.hpp"

using namespace SystemRender;

Process::Process(const Sys::Process& proc): Utility::TextArea(0),_proc(proc) { }

void Process::render(Render::Buffer& buf){
	std::stringstream ss;
	ss << this->_proc._stat.pid << " " << this->_proc._stat.name;
	this->text = ss.str();
	this->Utility::TextArea::render(buf);
}
