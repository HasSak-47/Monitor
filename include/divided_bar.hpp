#ifndef __DIVIDED_BAR_HPP__
#define __DIVIDED_BAR_HPP__

#include "progress_bar.hpp"


class DividedBar: public ProgressBar{
private:
    std::vector<ProgressBar> _sections;
public:
    DividedBar(){}
    DividedBar(size_t len, size_t _segments);

    [[deprecated("It does fucking nothing")]]
    void set_per(float per){}

    void set_pers(std::vector<float> pers);
    std::vector<ProgressBar>& get_bars();
};

#endif

