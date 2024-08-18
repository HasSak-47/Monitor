#include <algorithm>
#include <string>
#include <system_render/process.hpp>
#include <render/render.hpp>
#include <widgets/text_area.hpp>

using namespace SystemRender;

Processes::Processes(std::vector<Sys::Process>& ps): Widgets::Table(3),_ps(ps) {
    this->get_header(0) = "pid";
    this->get_header(1) = "name";
    this->get_header(2) = "mem MB";
}

void Processes::render(Render::Buffer& buf){
	std::sort(this->_ps.begin(), this->_ps.end(), [](const Sys::Process & a, const Sys::Process & b){
		return a.total() > b.total();
	});
    size_t max = std::max(this->_ps.size(), buf.get_height() - 1);
    this->set_dimentions(3, max);

    for(size_t i = 0; i < max; ++i){
        this->get_row_area(i, 0) = std::to_string(this->_ps[i]._stat.pid);
        this->get_row_area(i, 1) = this->_ps[i]._stat.name;
        size_t total = this->_ps[i].total() / 1000000;
        this->get_row_area(i, 2) = std::to_string(total);
    }

	this->Widgets::Table::render(buf);
}
