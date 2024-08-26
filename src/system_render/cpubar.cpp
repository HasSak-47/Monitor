#include <iostream>
#include <system_render/cpubar.hpp>
#include <system.hpp>
#include <iomanip>

#include <sstream>
#include "widgets/text_area.hpp"

using namespace SystemRender;

CPUBar::CPUBar() {
    this->add_section(Widgets::ProgressBar({0, 1, 0}));
    this->add_section(Widgets::ProgressBar({1, 0, 0}));
}

void CPUBar::render(Render::Buffer& buf){
    const auto& cpu = Sys::sys.stat.get_cpus_diff()[this->id];
    size_t total = cpu.idle;

    float user = cpu.user / (float)total;
    float kernel = cpu.system / (float)total;

    this->get_section(0).per = user;
    this->get_section(1).per = kernel;
    this->Widgets::DividedBar::render(buf);
    if(this->render_text){
        std::stringstream ss;
        ss << std::setw(5) << std::setprecision(3) << 100 * (kernel + user);

        auto sub = buf.get_subbuffer(buf.get_width() - 10, 0, 10, 1);
        Widgets::TextArea area(ss.str());
        area.render(sub);
    }
}
