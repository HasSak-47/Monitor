
#include <divided_bar.hpp>

DividedBar::DividedBar(size_t len, size_t segments):
ProgressBar(len){
    for(size_t i = 0; i < len; ++i)
        self._sections.push_back(ProgressBar(len, self.get_shared_buffer()));
}

void DividedBar::set_pers(std::vector<float> pers){
    let max = std::max(self._sections.size(), pers.size());
    mut total = 0;
    for(let sec : pers)
        total += sec;

    for(size_t i = 0; i < max; ++i){
        self._sections[i].set_per(total);
        total -= pers[i];
    }
}
